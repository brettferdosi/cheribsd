/*-
 * Copyright (c) 2003-2009 Silicon Graphics International Corp.
 * Copyright (c) 2011 Spectra Logic Corporation
 * Copyright (c) 2015 Alexander Motin <mav@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/users/kenm/FreeBSD-test2/sys/cam/ctl/ctl_ha.h#1 $
 * $FreeBSD$
 */

#ifndef _CTL_HA_H_
#define	_CTL_HA_H_

/*
 * CTL High Availability Modes:
 *
 * CTL_HA_MODE_ACT_STBY:  Commands are serialized to the master side.
 *			  No media access commands on slave side (Standby).
 * CTL_HA_MODE_SER_ONLY:  Commands are serialized to the master side.
 *			  Media can be accessed on both sides.
 * CTL_HA_MODE_XFER:	  Commands and data are forwarded to the
 *			  master side for execution.
 */
typedef enum {
	CTL_HA_MODE_ACT_STBY,
	CTL_HA_MODE_SER_ONLY,
	CTL_HA_MODE_XFER
} ctl_ha_mode;

/*
 * Communication channel IDs for various system components.  This is to
 * make sure one CTL instance talks with another, one ZFS instance talks
 * with another, etc.
 */
typedef enum {
	CTL_HA_CHAN_CTL,
	CTL_HA_CHAN_DATA,
	CTL_HA_CHAN_MAX
} ctl_ha_channel;

/*
 * HA communication event notification.  These are events generated by the
 * HA communication subsystem.
 *
 * CTL_HA_EVT_MSG_RECV:		Message received by the other node.
 * CTL_HA_EVT_LINK_CHANGE:	Communication channel status changed.
 */
typedef enum {
	CTL_HA_EVT_NONE,
	CTL_HA_EVT_MSG_RECV,
	CTL_HA_EVT_LINK_CHANGE,
	CTL_HA_EVT_MAX
} ctl_ha_event;

typedef enum {
	CTL_HA_STATUS_WAIT,
	CTL_HA_STATUS_SUCCESS,
	CTL_HA_STATUS_ERROR,
	CTL_HA_STATUS_INVALID,
	CTL_HA_STATUS_DISCONNECT,
	CTL_HA_STATUS_BUSY,
	CTL_HA_STATUS_MAX
} ctl_ha_status;

typedef enum {
	CTL_HA_DT_CMD_READ,
	CTL_HA_DT_CMD_WRITE,
} ctl_ha_dt_cmd;

struct ctl_ha_dt_req;

typedef void (*ctl_ha_dt_cb)(struct ctl_ha_dt_req *);

struct ctl_ha_dt_req {
	ctl_ha_dt_cmd	command;
	void		*context;
	ctl_ha_dt_cb	callback;
	int		ret;
	uint32_t	size;
	uint8_t		*local;
	uint8_t		*remote;
	TAILQ_ENTRY(ctl_ha_dt_req)	 links;
};

struct ctl_softc;
ctl_ha_status ctl_ha_msg_init(struct ctl_softc *softc);
void ctl_ha_msg_shutdown(struct ctl_softc *softc);
ctl_ha_status ctl_ha_msg_destroy(struct ctl_softc *softc);

typedef void (*ctl_evt_handler)(ctl_ha_channel channel, ctl_ha_event event,
				int param);
void ctl_ha_register_evthandler(ctl_ha_channel channel,
				ctl_evt_handler handler);

ctl_ha_status ctl_ha_msg_register(ctl_ha_channel channel,
    ctl_evt_handler handler);
ctl_ha_status ctl_ha_msg_recv(ctl_ha_channel channel, void *addr,
    size_t len, int wait);
ctl_ha_status ctl_ha_msg_send(ctl_ha_channel channel, const void *addr,
    size_t len, int wait);
ctl_ha_status ctl_ha_msg_send2(ctl_ha_channel channel, const void *addr,
    size_t len, const void *addr2, size_t len2, int wait);
ctl_ha_status ctl_ha_msg_abort(ctl_ha_channel channel);
ctl_ha_status ctl_ha_msg_deregister(ctl_ha_channel channel);

struct ctl_ha_dt_req * ctl_dt_req_alloc(void);
void ctl_dt_req_free(struct ctl_ha_dt_req *req);
ctl_ha_status ctl_dt_single(struct ctl_ha_dt_req *req);

typedef enum {
	CTL_HA_LINK_OFFLINE	= 0x00,
	CTL_HA_LINK_UNKNOWN	= 0x01,
	CTL_HA_LINK_ONLINE	= 0x02
} ctl_ha_link_state;

#endif /* _CTL_HA_H_ */
