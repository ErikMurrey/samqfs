/*
 * dev_log.c - Device log functions.
 */

/*
 *    SAM-QFS_notice_begin
 *
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at pkg/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at pkg/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 *    SAM-QFS_notice_end
 */

/*
 * Provide device logging facility for all device operation modules.
 * Also, the device log file may be mv'd or rm'd to keep it from growing
 * forever.
 */

#pragma ident "$Revision: 1.20 $"

static char *_SrcFile = __FILE__; /* Using __FILE__ makes duplicate strings */

/* Macros. */
#define	REOPEN_INTERVAL (1 * 60)	/* Reopen log file interval */

/* ANSI C headers. */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

/* POSIX headers. */
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

/* Solaris headers. */
#include <syslog.h>

/* SAM-FS headers. */
#include "aml/device.h"
#define	NEED_DL_NAMES
#include "aml/dev_log.h"
#undef NEED_DL_NAMES
#include "sam/types.h"
#include "sam/lib.h"
#include "aml/proto.h"
#include "aml/shm.h"
#include "sam/lint.h"
#if defined(lint)
#undef kill
#endif

/* Message table. */
/* Data generated by dev_log.awk program from dev_log.msg */
struct MsgsTable {
	int NumofMsgs;
	char **msgs;
};

#include "dev_logmsgs"

/* Private functions. */
static int OpenDevLog(dev_ent_t *un);

/* Private data. */

/* Imported data. */
extern shm_alloc_t master_shm;

/*
 * Write  message to device log file.
 * Note:  errno is preserved.
 */
void
DevLog(
	const uint_t MsgCtl,	/* Message control - packed with 3 arguments */
	dev_ent_t *un,		/* The device entry */
	const char *SrcFile,	/* Caller's source file. */
	const int SrcLine,	/* Caller's source line. */
	...)
{
	time_t	now;
	char	msg_buf[1024];
	char	*msg = msg_buf;
	char	*tdformat;
	int	SaveErrno;
	int	fd;
	int	event;
	int	category;
	int	msgnum;
	pid_t	pid;
	struct tm ltime;
	uint64_t len;

	/* Check event against flags - return if not selected */
	event = (MsgCtl >> 24) & 0xff;	/* Return if event not selected */
	if (un) {
		if (event != DL_all && !(un->log.flags & (1 << event))) {
			return;
		}
	}
	category = (MsgCtl >> 16) & 0xff;
	msgnum = MsgCtl & 0xffff;
	SaveErrno = errno;
	if (un) {
		now = time(NULL);
		pid = getpid();
		mutex_lock(&un->log.lmutex);
		if (pid == un->log.pid) {

			/*
			 * Close and reopen log file when necessary.
			 */
			if ((now - un->log.last_opened) > REOPEN_INTERVAL) {
				if (un->log.fd >= 0) {
					(void) close(un->log.fd);
				}
				if ((un->log.fd = OpenDevLog(un)) == -1) {
					errno = SaveErrno;
					mutex_unlock(&un->log.lmutex);
					return;
				}
				un->log.last_opened = now;
			}
			fd = un->log.fd;
			un->log.pid = pid;
		} else {
			fd = OpenDevLog(un);
			if (fd < 0) {
				errno = SaveErrno;
				mutex_unlock(&un->log.lmutex);
				return;
			}
		}
	}

	/* Enter elements in message. */

	/* Date and time. */
	if (un) {
		if (un->log.flags & (1 << DL_date)) {
			tdformat = "%Y/%m/%d %H:%M:%S";
		} else {
			tdformat = "%H:%M:%S";
		}
		localtime_r(&now, &ltime);
		strftime(msg, sizeof (msg_buf)-1, tdformat, &ltime);
		msg += strlen(msg);
		if (pid == un->log.pid) {
			*msg++ = ' ';
		} else {
			/* Mark not devlog owner. */
			*msg++ = '*';
		}

		/* Message number */
		sprintf(msg, "%d%03d ", category, msgnum);
		msg += strlen(msg);

		/* pid and thread id */
		sprintf(msg, "[%ld:%d] ", getpid(), pthread_self());
		msg += strlen(msg);

		/* Source module */
		if ((un->log.flags & (1 << DL_module)) && SrcFile != NULL) {
			sprintf(msg, "%s:%d ", SrcFile, SrcLine);
			msg += strlen(msg);
		}
	} else {
		sprintf(msg, "%d%03d ", category, msgnum);
		msg += strlen(msg);
		sprintf(msg, "%s:%d ", SrcFile, SrcLine);
		msg += strlen(msg);
	}

	/* Trace event */
	switch (event) {
	case DL_err:
		strcpy(msg, "Error: ");
		break;
	case DL_syserr:
		strcpy(msg, "System error: ");
		break;
	case DL_retry:
		sprintf(msg, "Retry: ");
		break;
	default:
		if (un) {
			if ((un->log.flags & (1 << DL__event)) &&
			    event < DL_MAX) {
				sprintf(msg, "%s ", DL_names[event]);
			}
		} else {
			if (event < DL_MAX) {
				sprintf(msg, "%s ", DL_names[event]);
			}
		}
	}
	msg += strlen(msg);

	/* The message */
	{
		va_list args;
		char *fmt;

		va_start(args, SrcLine);
		if (category == 0 && msgnum == 0) {
			/* Temporary message supplied */
			fmt = va_arg(args, char *);
			vsprintf(msg, fmt, args);
		} else if (category < DevlogMsgsTableNum &&
		    msgnum < DevlogMsgsTable[category].NumofMsgs) {

			/* Message from table */
			fmt = DevlogMsgsTable[category].msgs[msgnum];
			vsprintf(msg, fmt, args);
		} else {
			sprintf(msg,
			    "*** Invalid message %d %03d",
			    category, msgnum);
		}
		va_end(args);
		msg += strlen(msg);
	}

	/* System call error number */
	if (event == DL_syserr && SaveErrno != 0) {
		strcpy(msg, ": ");
		msg += strlen(msg);
		len = (uint64_t)sizeof (msg_buf) -
		    ((uint64_t)msg - (uint64_t)msg_buf);
		(void) StrFromErrno(SaveErrno, msg, len);
		msg += strlen(msg);
	}

	*msg++ = '\n';
	*msg = '\0';

	/* If the un is NULL, then syslog it */
	if (un) {
		len = (uint64_t)msg - (uint64_t)msg_buf;
		if (write(fd, msg_buf, len) < 0) {
			sam_syslog(LOG_INFO, "write devlog: %s",
			    strerror(errno));
		}
		if (pid != un->log.pid) {
			(void) close(fd);
		}
		mutex_unlock(&un->log.lmutex);
	} else {
		sam_syslog(LOG_ERR,
		    "DevLog called with null device entry : message : %s",
		    msg_buf);
	}
	errno = SaveErrno;
}


/*
 * Log cdb data.
 */
void
DevLogCdb(dev_ent_t *un)
{
	uchar_t *dp;
	int	line, field;

	dp = un->cdb;
	for (line = 0; line < 2; line++) {
		char	buf[50], *bp;

		bp = buf;
		for (field = 0; field < (SAM_CDB_LENGTH / 2); field++) {
			sprintf(bp, "%02x ", *dp++);
			bp += 3;
		}
		if (line == 0) {
			DevLog(DL_ALL(0), "cdb - %s", buf);
		} else {
			DevLog(DL_ALL(0), "      %s", buf);
		}
	}
}


/*
 * Log sense data.
 */
void
DevLogSense(dev_ent_t *un)
{
	uchar_t *dp;
	int	line, field;

	dp = (uchar_t *)SHM_REF_ADDR(un->sense);
	for (line = 0; line < 2; line++) {
		char	buf[50], *bp;

		bp = buf;
		for (field = 0; field < 10; field++) {
			sprintf(bp, "%02x ", *dp++);
			bp += 3;
		}
		if (line == 0) {
			DevLog(DL_ALL(0), "sense - %s", buf);
		} else {
			DevLog(DL_ALL(0), "        %s", buf);
		}
	}
}


/*
 * Attach the device log to the owning process.
 */
void
AttachDevLog(dev_ent_t *un)
{

	mutex_lock(&un->log.lmutex);
	if (un->log.pid != 0 && kill(un->log.pid, 0) == 0) {
		sam_syslog(LOG_ERR,
		    "Cannot attach to log device %d owned by %d",
		    un->eq, un->log.pid);
		return;
	}

	if (un->log.fd > 0) {
		close(un->log.fd);
	}
	un->log.fd = OpenDevLog(un);
	un->log.pid = getpid();
	mutex_unlock(&un->log.lmutex);
	DevLog(DL_ALL(0), "Attached to process %d", un->log.pid);
}


/*
 * Initialize device log.
 */
void
InitDevLog(dev_ent_t *un)
{
	mutex_init(&un->log.lmutex, USYNC_PROCESS, NULL);
	un->log.pid = 0;
	DevLog(DL_ALL(0), "Initialized. %s", device_to_nm(un->type));
}


/*
 * Open the device log.
 */
static int
OpenDevLog(dev_ent_t *un)
{
	char	filename[MAXPATHLEN];
	int	fd;

	sprintf(filename, "%s/%02d", DEVLOG_NAME, un->eq);
	if ((fd = open(filename,
	    O_WRONLY | O_CREAT | O_APPEND | SAM_O_LARGEFILE, 0644)) < 0) {

		sam_syslog(LOG_WARNING, "Could not create %s: %m", filename);
		un->log.flags = 0;	/* Prevent re-entry */
		return (-1);
	}
	return (fd);
}

#if defined(TEST)
int
main()
{
	dev_ent_t dev, *un;

	un = &dev;
	un->eq = 1;
	un->type = 0x1283;
	InitDevLog(un);
	DevLog(DL_ALL(0), "This is a test");
	DevLog(DL_DETAIL(2001));
	DevLog(DL_ERR(2002));
	open("XXX", 0);
	DevLog(DL_SYSERR(2011), 1);
	DevLog(DL_ALL(2022));
	DevLog(DL_ALL(9999));
}
#endif /* defined(TEST) */
