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

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

/******************************************************************
 * Define compile-time options below.
 ******************************************************************/

#define DROPBEAR_PORT 22

// BRCM begin:
/* Default hostkey paths - these can be specified on the command line */
//#define DSS_PRIV_FILENAME "/etc/dropbear_dss_host_key"
//#define RSA_PRIV_FILENAME "/etc/dropbear_rsa_host_key"
#define DSS_PRIV_FILENAME "/etc/dss_host_key"
#define RSA_PRIV_FILENAME "/etc/rsa_host_key"
// BRCM end

/* Disable X11 Forwarding */
/*#define DISABLE_X11FWD*/
// BRCM add next line
#define DISABLE_X11FWD

/* Disable TCP Fowarding */
/* NOTE: TCP forwarding is still work-in-progress, -L forwarding should work,
 * enable TCP forwarding at your own risk. */
#define DISABLE_TCPFWD

/* Disable Authentication Agent Forwarding */
/*#define DISABLE_AGENTFWD*/

/* Encryption - at least one required.
 * RFC Draft requires 3DES, and recommends Blowfish, AES128 & Twofish128 */
// BRCM  #define DROPBEAR_AES128_CBC
// BRCM  #define DROPBEAR_BLOWFISH_CBC
// BRCM  #define DROPBEAR_TWOFISH128_CBC
#define DROPBEAR_3DES_CBC

/* Integrity - at least one required.
 * RFC Draft requires sha1-hmac, and recommends md5-hmac.
 * Note: there's no point disabling sha1 to save space, since it's used in the
 * for the random number generator and public-key cryptography anyway.
 * Disabling it here will just stop it from being used as the integrity portion
 * of the ssh protocol */
#define DROPBEAR_SHA1_HMAC
#define DROPBEAR_MD5_HMAC

/* Hostkey/public key algorithms - at least one required, these are used
 * for hostkey as well as for verifying signatures with pubkey auth.
 * SSH2 RFC Draft requires dss, recommends rsa */
#define DROPBEAR_RSA
// BRCM disable DSS for signing
//#define DROPBEAR_DSS

/* Define DSS_PROTOK to use PuTTY's method of generating the value k for dss,
 * rather than just from the random byte source. Undefining this will save you
 * ~4k in binary size with static uclibc, but your DSS hostkey could be exposed
 * if the random number source isn't good. In general this isn't required */
/* #define DSS_PROTOK */

/* Whether to do reverse DNS lookups. This is advisable, though will add
 * code size with gethostbyname() etc, so for very small environments where
 * you are statically linking, you might want to undefine this */
// BRCM #define DO_HOST_LOOKUP

/* Authentication types to enable, at least one required.
   RFC Draft requires pubkey auth, and recommends password */
#define DROPBEAR_PASSWORD_AUTH
// BRCM Commented next line
//#define DROPBEAR_PUBKEY_AUTH

/* Random device to use - you must specify _one only_.
 * DEV_RANDOM is recommended on hosts with a good /dev/urandom, otherwise use
 * PRNGD and run prngd, specifying the socket. This device must be able to
 * produce a large amount of random data, so using /dev/random or Entropy
 * Gathering Daemon (egd) may result in halting, as it waits for more random
 * data */
#define DROPBEAR_DEV_URANDOM /* use /dev/urandom */

/*#undef DROPBEAR_PRNGD */ /* use prngd socket - you must manually set up prngd
							  to produce output */
#define DROPBEAR_PRNGD_SOCKET "/var/run/dropbear-rng"

/* Specify the number of clients we will allow to be connected but
 * not yet authenticated. After this limit, connections are rejected */
//BRCM change 30 to 1
#define MAX_UNAUTH_CLIENTS 1

/* Maximum number of failed authentication tries */
#define MAX_AUTH_TRIES 10

/* The file to store the daemon's process ID, for shutdown scripts etc */
#define DROPBEAR_PIDFILE "/var/run/dropbear.pid"

/* The command to invoke for xauth when using X11 forwarding.
 * "-q" for quiet */
#define XAUTH_COMMAND "/usr/bin/X11/xauth -q"

/*******************************************************************
 * You shouldn't edit below here unless you know you need to.
 *******************************************************************/

#define DROPBEAR_VERSION "0.36"
#define LOCAL_IDENT "SSH-2.0-dropbear_" DROPBEAR_VERSION
#define PROGNAME "dropbear"

/* Time to wait before sending reply on fail */
#define FAIL_SLEEP_TIME 2

/* Timeouts in seconds */
#define SELECT_TIMEOUT 20
/* Spec recommends after one hour or 1 gigabyte of data */
#define KEX_REKEY_TIMEOUT 3600
#define KEX_REKEY_DATA (1<<30) /* 2^30 == 1GB, this value must be < INT_MAX */
/* Close connections to clients which haven't authorised after AUTH_TIMEOUT */
#define AUTH_TIMEOUT 600 /* 10 minutes is recommended */

/* success/failure defines */
#define DROPBEAR_SUCCESS 0
#define DROPBEAR_FAILURE -1

/* various algorithm identifiers */
#define DROPBEAR_KEX_DH_GROUP1 0

#define DROPBEAR_SIGNKEY_ANY 0
#define DROPBEAR_SIGNKEY_RSA 1
#define DROPBEAR_SIGNKEY_DSS 2

#define DROPBEAR_COMP_NONE 0
#define DROPBEAR_COMP_ZLIB 1

/* Required for pubkey auth */
#ifdef DROPBEAR_PUBKEY_AUTH
#define DROPBEAR_SIGNKEY_VERIFY
#endif

/* SHA1 is 20 bytes == 160 bits */
#define SHA1_HASH_SIZE 20
/* SHA512 is 64 bytes == 512 bits */
#define SHA512_HASH_SIZE 64

/* largest of MD5 and SHA1 */
#define MAX_MAC_LEN SHA1_HASH_SIZE


#define MAX_KEY_LEN 24 /* 3DES requires a 24 byte key */
#define MAX_IV_LEN 20 /* must be same as max blocksize, 
						 and >= SHA1_HASH_SIZE */
#define MAX_MAC_KEY 20

#define MAX_NAME_LEN 64 /* maximum length of a protocol name, isn't
						   explicitly specified for all protocols (just
						   for algos) but seems valid */

#define MAX_PROPOSED_ALGO 20

/* size/count limits */
#define MAX_LISTEN_ADDR 10

#define MAX_PACKET_LEN 35000
#define MIN_PACKET_LEN 16
#define MAX_PAYLOAD_LEN 32768

#define MAX_TRANS_PAYLOAD_LEN 32768
#define MAX_TRANS_PACKET_LEN (MAX_TRANS_PAYLOAD_LEN+50)

#define MAX_TRANS_WINDOW 500000000 /* 500MB is sufficient, stopping overflow */
#define MAX_TRANS_WIN_INCR 500000000 /* overflow prevention */

#define MAX_BANNER_SIZE 2000 /* this is 25*80 chars, any more is foolish */

#define MAX_STRING_LEN 1400 /* ~ MAX_PROPOSED_ALGO * MAX_NAME_LEN */

#define DEV_URANDOM "/dev/urandom"

/* the number of NAME=VALUE pairs to malloc for environ, if we don't have
 * the clearenv() function */
#define ENV_SIZE 100

#define MAX_CMD_LEN 1024 /* max length of a command */
#define MAX_TERM_LEN 200 /* max length of TERM name */

#define MAX_HOST_LEN 254 /* max hostname len for tcp fwding */

#define DROPBEAR_MAX_PORTS 10 /* max number of ports which can be specified,
								 ipv4 and ipv6 don't count twice */

#define _PATH_TTY "/dev/tty"

#ifdef DISABLE_TCPFWD
#define DISABLE_LOCALTCPFWD
#define DISABLE_REMOTETCPFWD
#endif

#endif /* _OPTIONS_H_ */
