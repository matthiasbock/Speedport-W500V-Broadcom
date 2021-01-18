/*
 * Automatically generated header file: don't edit
 */

#define AUTOCONF_INCLUDED

/* Version Number */
#define BB_VER "1.00"
#define BB_BT "2007.04.19-08:54+0000"

#define HAVE_DOT_CONFIG 1

/*
 * General Configuration
 */
#undef CONFIG_FEATURE_BUFFERS_USE_MALLOC
#define CONFIG_FEATURE_BUFFERS_GO_ON_STACK 1
#undef CONFIG_FEATURE_BUFFERS_GO_IN_BSS
#define CONFIG_FEATURE_VERBOSE_USAGE 1
#undef CONFIG_FEATURE_INSTALLER
#undef CONFIG_LOCALE_SUPPORT
#undef CONFIG_FEATURE_DEVFS
#undef CONFIG_FEATURE_DEVPTS
#undef CONFIG_FEATURE_CLEAN_UP
#undef CONFIG_FEATURE_SUID
#undef CONFIG_SELINUX

/*
 * Build Options
 */
#undef CONFIG_STATIC
#undef CONFIG_LFS
#define USING_CROSS_COMPILER 1
#define CROSS_COMPILER_PREFIX "/opt/toolchains/uclibc-crosstools/bin/mips-linux-uclibc-"
#define EXTRA_CFLAGS_OPTIONS ""

/*
 * Installation Options
 */
#undef CONFIG_INSTALL_NO_USR
#define PREFIX "./_install"

/*
 * Archival Utilities
 */
#undef CONFIG_AR
#undef CONFIG_BUNZIP2
#undef CONFIG_CPIO
#undef CONFIG_DPKG
#undef CONFIG_DPKG_DEB
#undef CONFIG_GUNZIP
#undef CONFIG_GZIP
#undef CONFIG_RPM2CPIO
#undef CONFIG_RPM
#undef CONFIG_TAR
#undef CONFIG_UNCOMPRESS
#undef CONFIG_UNZIP

/*
 * Coreutils
 */
#undef CONFIG_BASENAME
#undef CONFIG_CAL
#define CONFIG_CAT 1
#undef CONFIG_CHGRP
#undef CONFIG_CHMOD
#undef CONFIG_CHOWN
#undef CONFIG_CHROOT
#undef CONFIG_CMP
#undef CONFIG_CP
#undef CONFIG_CUT
#undef CONFIG_DATE
#undef CONFIG_DD
#define CONFIG_DF 1
#undef CONFIG_DIRNAME
#undef CONFIG_DOS2UNIX
#undef CONFIG_DU
#define CONFIG_ECHO 1
#define CONFIG_FEATURE_FANCY_ECHO 1
#undef CONFIG_ENV
#define CONFIG_EXPR 1
#define CONFIG_FALSE 1

/*
 * false (forced enabled for use with shell)
 */
#undef CONFIG_FOLD
#undef CONFIG_HEAD
#undef CONFIG_HOSTID
#undef CONFIG_ID
#undef CONFIG_INSTALL
#undef CONFIG_LENGTH
#undef CONFIG_LN
#undef CONFIG_LOGNAME
#define CONFIG_LS 1
#define CONFIG_FEATURE_LS_FILETYPES 1
#define CONFIG_FEATURE_LS_FOLLOWLINKS 1
#define CONFIG_FEATURE_LS_RECURSIVE 1
#define CONFIG_FEATURE_LS_SORTFILES 1
#define CONFIG_FEATURE_LS_TIMESTAMPS 1
#define CONFIG_FEATURE_LS_USERNAME 1
#define CONFIG_FEATURE_LS_COLOR 1
#undef CONFIG_MD5SUM
#define CONFIG_MKDIR 1
#undef CONFIG_MKFIFO
#undef CONFIG_MKNOD
#undef CONFIG_MV
#undef CONFIG_OD
#undef CONFIG_PRINTF
#define CONFIG_PWD 1
#undef CONFIG_REALPATH
#define CONFIG_RM 1
#undef CONFIG_RMDIR
#undef CONFIG_SEQ
#undef CONFIG_SHA1SUM
#undef CONFIG_SLEEP
#undef CONFIG_SORT
#undef CONFIG_STTY
#undef CONFIG_SYNC
#undef CONFIG_TAIL
#undef CONFIG_TEE
#define CONFIG_TEST 1

/*
 * test (forced enabled for use with shell)
 */
#undef CONFIG_FEATURE_TEST_64
#undef CONFIG_TOUCH
#undef CONFIG_TR
#define CONFIG_TRUE 1

/*
 * true (forced enabled for use with shell)
 */
#define CONFIG_TTY 1
#undef CONFIG_UNAME
#undef CONFIG_UNIQ
#undef CONFIG_USLEEP
#undef CONFIG_UUDECODE
#undef CONFIG_UUENCODE
#undef CONFIG_WATCH
#undef CONFIG_WC
#undef CONFIG_WHO
#undef CONFIG_WHOAMI
#undef CONFIG_YES

/*
 * Common options for ls and more
 */
#define CONFIG_FEATURE_AUTOWIDTH 1

/*
 * Common options for df, du, ls
 */
#undef CONFIG_FEATURE_HUMAN_READABLE

/*
 * Console Utilities
 */
#undef CONFIG_CHVT
#undef CONFIG_CLEAR
#undef CONFIG_DEALLOCVT
#undef CONFIG_DUMPKMAP
#undef CONFIG_LOADFONT
#undef CONFIG_LOADKMAP
#undef CONFIG_OPENVT
#undef CONFIG_RESET
#undef CONFIG_SETKEYCODES

/*
 * Debian Utilities
 */
#undef CONFIG_MKTEMP
#undef CONFIG_PIPE_PROGRESS
#undef CONFIG_READLINK
#undef CONFIG_RUN_PARTS
#undef CONFIG_START_STOP_DAEMON
#undef CONFIG_WHICH

/*
 * Editors
 */
#undef CONFIG_AWK
#undef CONFIG_PATCH
#define CONFIG_SED 1
#undef CONFIG_VI

/*
 * Finding Utilities
 */
#undef CONFIG_FIND
#undef CONFIG_GREP
#undef CONFIG_XARGS

/*
 * Init Utilities
 */
#define CONFIG_INIT 1
#define CONFIG_FEATURE_USE_INITTAB 1
#define CONFIG_FEATURE_INITRD 1
#undef CONFIG_FEATURE_INIT_COREDUMPS
#undef CONFIG_FEATURE_EXTRA_QUIET
#undef CONFIG_HALT
#undef CONFIG_POWEROFF
#define CONFIG_REBOOT 1
#undef CONFIG_MESG

/*
 * Login/Password Management Utilities
 */
#undef CONFIG_USE_BB_PWD_GRP
#undef CONFIG_ADDGROUP
#undef CONFIG_DELGROUP
#undef CONFIG_ADDUSER
#undef CONFIG_DELUSER
#undef CONFIG_GETTY
#undef CONFIG_LOGIN
#undef CONFIG_PASSWD
#undef CONFIG_SU
#undef CONFIG_SULOGIN
#undef CONFIG_VLOCK

/*
 * Miscellaneous Utilities
 */
#undef CONFIG_ADJTIMEX
#undef CONFIG_CROND
#undef CONFIG_CRONTAB
#undef CONFIG_DC
#undef CONFIG_DEVFSD
#undef CONFIG_LAST
#undef CONFIG_HDPARM
#undef CONFIG_MAKEDEVS
#undef CONFIG_MT
#undef CONFIG_RX
#undef CONFIG_STRINGS
#undef CONFIG_TIME
#undef CONFIG_WATCHDOG
#define CONFIG_SYSINFO 1

/*
 * Linux Module Utilities
 */
#define CONFIG_INSMOD 1
#undef CONFIG_FEATURE_2_4_MODULES
#define CONFIG_FEATURE_2_6_MODULES 1
#undef CONFIG_LSMOD
#undef CONFIG_MODPROBE
#define CONFIG_RMMOD 1
#undef CONFIG_FEATURE_CHECK_TAINTED_MODULE

/*
 * Networking Utilities
 */
#undef CONFIG_FEATURE_IPV6
#undef CONFIG_ARPING
#define CONFIG_SENDARP 1
#define CONFIG_TFTPD 1
#undef CONFIG_FTPGET
#undef CONFIG_FTPPUT
#undef CONFIG_HOSTNAME
#undef CONFIG_HTTPD
#define CONFIG_IFCONFIG 1
#define CONFIG_FEATURE_IFCONFIG_STATUS 1
#undef CONFIG_FEATURE_IFCONFIG_SLIP
#undef CONFIG_FEATURE_IFCONFIG_MEMSTART_IOADDR_IRQ
#define CONFIG_FEATURE_IFCONFIG_HW 1
#define CONFIG_FEATURE_IFCONFIG_BROADCAST_PLUS 1
#undef CONFIG_IFUPDOWN
#undef CONFIG_INETD
#undef CONFIG_IP
#undef CONFIG_IPCALC
#undef CONFIG_IPADDR
#undef CONFIG_IPLINK
#undef CONFIG_IPROUTE
#undef CONFIG_IPTUNNEL
#undef CONFIG_NAMEIF
#undef CONFIG_NC
#undef CONFIG_NETSTAT
#undef CONFIG_NSLOOKUP
#define CONFIG_PING 1
#undef CONFIG_FEATURE_FANCY_PING
#define CONFIG_ROUTE 1
#undef CONFIG_TELNET
#undef CONFIG_TELNETD
#define CONFIG_TFTP 1
#define CONFIG_FEATURE_TFTP_GET 1
#define CONFIG_FEATURE_TFTP_PUT 1
#undef CONFIG_FEATURE_TFTP_BLOCKSIZE
#undef CONFIG_FEATURE_TFTP_DEBUG
#undef CONFIG_TRACEROUTE
#define CONFIG_VCONFIG 1
#undef CONFIG_WGET

/*
 * udhcp Server/Client
 */
#undef CONFIG_UDHCPD
#undef CONFIG_UDHCPC

/*
 * Process Utilities
 */
#undef CONFIG_FREE
#define CONFIG_KILL 1
#undef CONFIG_KILLALL
#undef CONFIG_PIDOF
#define CONFIG_PS 1
#undef CONFIG_RENICE
#undef CONFIG_TOP
#undef CONFIG_UPTIME
#undef CONFIG_SYSCTL

/*
 * Another Bourne-like Shell
 */
#undef CONFIG_FEATURE_SH_IS_ASH
#undef CONFIG_FEATURE_SH_IS_HUSH
#undef CONFIG_FEATURE_SH_IS_LASH
#define CONFIG_FEATURE_SH_IS_MSH 1
#undef CONFIG_FEATURE_SH_IS_NONE
#undef CONFIG_ASH
#undef CONFIG_HUSH
#undef CONFIG_LASH
#define CONFIG_MSH 1

/*
 * Bourne Shell Options
 */
#undef CONFIG_FEATURE_SH_EXTRA_QUIET
#define CONFIG_FEATURE_SH_STANDALONE_SHELL 1
#define CONFIG_FEATURE_COMMAND_EDITING 1
#define CONFIG_FEATURE_COMMAND_HISTORY 15
#undef CONFIG_FEATURE_COMMAND_TAB_COMPLETION
#undef CONFIG_FEATURE_SH_FANCY_PROMPT

/*
 * System Logging Utilities
 */
#define CONFIG_SYSLOGD 1
#undef CONFIG_FEATURE_ROTATE_LOGFILE
#define CONFIG_FEATURE_REMOTE_LOG 1
#define CONFIG_FEATURE_IPC_SYSLOG 1
#define CONFIG_FEATURE_IPC_SYSLOG_BUFFER_SIZE 16
#define CONFIG_LOGREAD 1
#undef CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING
#define CONFIG_KLOGD 1
#define CONFIG_LOGGER 1

/*
 * Linux System Utilities
 */
#define CONFIG_DMESG 1
#undef CONFIG_FBSET
#undef CONFIG_FDFLUSH
#undef CONFIG_FDFORMAT
#undef CONFIG_FDISK
#undef CONFIG_FREERAMDISK
#undef CONFIG_FSCK_MINIX
#undef CONFIG_MKFS_MINIX
#undef CONFIG_GETOPT
#undef CONFIG_HEXDUMP
#undef CONFIG_HWCLOCK
#undef CONFIG_LOSETUP
#undef CONFIG_MKSWAP
#undef CONFIG_MORE
#undef CONFIG_PIVOT_ROOT
#undef CONFIG_RDATE
#undef CONFIG_SWAPONOFF
#define CONFIG_MOUNT 1
#undef CONFIG_NFSMOUNT
#undef CONFIG_UMOUNT

/*
 * Common options for mount/umount
 */
#undef CONFIG_FEATURE_MOUNT_LOOP
#undef CONFIG_FEATURE_MTAB_SUPPORT

/*
 * Debugging Options
 */
#undef CONFIG_DEBUG
