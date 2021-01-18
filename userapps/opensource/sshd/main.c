/*
 * Dropbear - a SSH2 server
 * 
 * Copyright (c) 2002,2003 Matt Johnston
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. */

#include "includes.h"
#include "util.h"
#include "session.h"
#include "buffer.h"
#include "signkey.h"
#include "runopts.h"

// BRCM add next line
#include <netinet/in.h>
#include "bcmprocfs.h"
#include "cliapi.h"
#include "syscall.h"

static int listensockets(int *sock, runopts * opts, int *maxfd);
static void sigchld_handler(int dummy);
static void sigsegv_handler(int);
static void sigintterm_handler(int fish);

static int childpipes[MAX_UNAUTH_CLIENTS];

// BRCM begin
int glbAccessMode;       // gloable for BcmCli_run access mode
void dropbear_main(void);

void BcmSSHD_Init(void) {
   int fd;
   int pid;

   pid = fork();
   if ( pid == -1 ) {
      printf("\nUnable to spawn dropbear server\n");
      return;
   }
   if ( pid == 0 ) {
      if ((fd = open("/dev/bcm", O_RDWR)) < 0)
         perror("Dropbear:open");
      if (ioctl(fd, RENAME_SSHD, 0) < 0)
         perror("ioctl");
      if ( fd > 0)
	      close(fd);
      dropbear_main();
   }
}


void dropbear_main(void) {
	fd_set fds;
	struct timeval seltimeout;
	unsigned int i, j;
	int val;
	int maxsock = -1;
	struct sockaddr remoteaddr;
	int remoteaddrlen;
	int listensocks[MAX_LISTEN_ADDR];
	unsigned int listensockcount = 0;
	runopts * opts;
	FILE * pidfile;

	int childsock;
	pid_t childpid;
	int childpipe[2];
	struct sigaction sa_chld;

	/* get commandline options */
	opts = getrunopts();
	/* see printhelp() for options */

#ifndef DISABLE_SYSLOG
	if (usingsyslog) {
		startsyslog();
	}
#endif

	/* create a PID file so that we can be killed easily */
	pidfile = fopen(DROPBEAR_PIDFILE, "w");
	if (pidfile) {
		fprintf(pidfile, "%d\n", getpid());
		fclose(pidfile);
	}

	/* set up cleanup handler */
	if (signal(SIGINT, sigintterm_handler) == SIG_ERR || 
		signal(SIGTERM, sigintterm_handler) == SIG_ERR) {
		dropbear_exit("signal() error");
	}

	/* catch and reap zombie children */
	sa_chld.sa_handler = sigchld_handler;
	sa_chld.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sa_chld, NULL) < 0) {
		dropbear_exit("signal() error");
	}
	if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
		dropbear_exit("signal() error");
	}


	/* sockets to identify pre-authenticated clients */
	for (i = 0; i < MAX_UNAUTH_CLIENTS; i++) {
		childpipes[i] = -1;
	}
	
	/* Set up the listening sockets */
	/* XXX XXX ports */
	listensockcount = listensockets(listensocks, opts, &maxsock);

	/* incoming connection select loop */
	for(;;) {

		FD_ZERO(&fds);
		
		seltimeout.tv_sec = 60;
		seltimeout.tv_usec = 0;
		
		/* listening sockets */
		for (i = 0; i < listensockcount; i++) {
			FD_SET(listensocks[i], &fds);
		}

		/* pre-authentication clients */
      for (i = 0; i < MAX_UNAUTH_CLIENTS; i++) {
			if (childpipes[i] >= 0) 
			FD_SET(childpipes[i], &fds);
			maxsock = MAX(maxsock, childpipes[i]);
		}

		val = select(maxsock+1, &fds, NULL, NULL, &seltimeout);

		if (exitflag) {
			unlink(DROPBEAR_PIDFILE);
			dropbear_exit("Terminated by signal");
		}
		
		if (val == 0) {
			/* timeout reached */
			continue;
		}

		if (val < 0) {
			if (errno == EINTR) {
				continue;
			}
			dropbear_exit("Listening socket error");
		}

		/* close fds which have been authed or closed - auth.c handles
		 * closing the auth sockets on success */
		for (i = 0; i < MAX_UNAUTH_CLIENTS; i++) {
			if (childpipes[i] >= 0 && FD_ISSET(childpipes[i], &fds)) {
				close(childpipes[i]);
				childpipes[i] = -1;
			}
		}

		/* handle each socket which has something to say */
		for (i = 0; i < listensockcount; i++) {
			if (!FD_ISSET(listensocks[i], &fds)) 
				continue;

			/* child connection XXX - ip6 stuff here */
			remoteaddrlen = sizeof(struct sockaddr_in);

            childsock = accept(listensocks[i], &remoteaddr, &remoteaddrlen);
			if (childsock < 0) {
				/* accept failed */
				continue;
			}
            glbAccessMode = bcmCheckEnable("ssh", ((struct sockaddr_in *)&remoteaddr)->sin_addr);
            if (glbAccessMode == CLI_ACCESS_DISABLED) {
                close(childsock);
                continue;
            }
            // get the interface name for tftp (for not killing the process it is on).
            char ifName[32];
            FILE *ifc_fp;
            ifName[0] = '\0';
            if (bcmGetIntfNameSocket(childsock, ifName) == 0) {
                if (ifName[0] != '\0') {
                    if (!(ifc_fp = fopen("/var/run/sshd_ifc", "w"))) {
                        perror("/var/run/sshd_ifc");
                        return errno;
                    }
                    fprintf(ifc_fp, "%s\n", ifName);
                    fclose(ifc_fp);
                }
            }
			/* check for max number of connections not authorised */
			for (j = 0; j < MAX_UNAUTH_CLIENTS; j++) {
				if (childpipes[j] < 0) {
					break;
				}
			}

			if (j == MAX_UNAUTH_CLIENTS) {
				/* no free connections */
				/* TODO - possibly log, though this would be an easy way
				 * to fill logs/disk */
				close(childsock);
				continue;
			}

			if (pipe(childpipe) < 0) {
				TRACE(("error creating child pipe"));
				close(childsock);
				continue;
			}

			if ((childpid = fork()) == 0) {

				/* child */
#ifdef DEBUG_FORKGPROF
				extern void _start(void), etext(void);
				monstartup((u_long)&_start, (u_long)&etext);
#endif /* DEBUG_FORKGPROF */
				if (setpgid(0,0) < 0) {
					dropbear_exit("Error creating child");
				}

				/* make sure we close sockets */
				for (i = 0; i < listensockcount; i++) {
					if (m_close(listensocks[i]) == DROPBEAR_FAILURE) {
						dropbear_exit("Couldn't close socket");
					}
				}

				if (m_close(childpipe[0]) == DROPBEAR_FAILURE) {
					dropbear_exit("Couldn't close socket");
				}
				/* start the session */
				child_session(childsock, opts, childpipe[1], &remoteaddr);
				/* don't return */
				assert(0);
			}
			
			/* parent */
			childpipes[j] = childpipe[0];
			if (m_close(childpipe[1]) == DROPBEAR_FAILURE
					|| m_close(childsock) == DROPBEAR_FAILURE) {
				dropbear_exit("Couldn't close socket");
			}
		}
	} /* for(;;) loop */

	/* don't reach here */
   return;
}
// BRCM end

/* catch + reap zombie children */
static void sigchld_handler(int fish) {
	struct sigaction sa_chld;
// BRCM begin
   fish = 1;
// BRCM end

	while(waitpid(-1, NULL, WNOHANG) > 0); 

	sa_chld.sa_handler = sigchld_handler;
	sa_chld.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sa_chld, NULL) < 0) {
		dropbear_exit("signal() error");
	}
}

/* catch any segvs */
static void sigsegv_handler(int fish) {
	fprintf(stderr, "Aiee, segfault! You should probably report "
			"this as a bug to the developer\n");
	exit(EXIT_FAILURE);
}

/* catch ctrl-c or kill */
static void sigintterm_handler(int fish) {

	exitflag = 1;
}

/* Set up listening sockets for all the requested ports */
static int listensockets(int *sock, runopts * opts, int *maxfd) {
	
	int listensock; /* listening fd */
	struct sockaddr_in listen_addr;
	struct linger linger;
	unsigned int i;
	int val;

	for (i = 0; i < opts->portcount; i++) {

		/* iterate through all the sockets to listen on */
		listensock = socket(PF_INET, SOCK_STREAM, 0);
		if (listensock < 0) {
			dropbear_exit("Failed to create socket");
		}

		val = 1;
		/* set to reuse, quick timeout */
		setsockopt(listensock, SOL_SOCKET, SO_REUSEADDR,
				(void*) &val, sizeof(val));
		linger.l_onoff = 1;
		linger.l_linger = 5;
		setsockopt(listensock, SOL_SOCKET, SO_LINGER,
				(void*)&linger, sizeof(linger));

		/* disable nagle */
		setsockopt(listensock, IPPROTO_TCP, TCP_NODELAY,
				(void*)&val, sizeof(val));

		listen_addr.sin_family = AF_INET;
		listen_addr.sin_port = htons(opts->ports[i]);
		listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		memset(&(listen_addr.sin_zero), '\0', 8);

		if (bind(listensock, (struct sockaddr *)&listen_addr,
					sizeof(listen_addr)) < 0) {
			dropbear_exit("Bind failed port %d", opts->ports[i]);
		}

		/* listen */
		if (listen(listensock, 20) < 0) { /* TODO set listen count */
			dropbear_exit("Listen failed");
		}

		/* nonblock */
		if (fcntl(listensock, F_SETFL, O_NONBLOCK) < 0) {
			dropbear_exit("Failed to set non-blocking");
		}

		sock[i] = listensock;
		*maxfd = MAX(listensock, *maxfd);
	}

	return opts->portcount;
}
