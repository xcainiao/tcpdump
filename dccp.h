/* @(#) $Header: /tcpdump/master/tcpdump/dccp.h,v 1.5 2006-11-02 09:05:23 hannes Exp $ (LBL) */
/*
 * Copyright (C) Arnaldo Carvalho de Melo 2004
 * Copyright (C) Ian McDonald 2005 <iam4@cs.waikato.ac.nz>
 * Copyright (C) Yoshifumi Nishida 2005
 *
 * This software may be distributed either under the terms of the
 * BSD-style license that accompanies tcpdump or the GNU GPL version 2
 */

#ifndef __DCCP_HDR__
#define __DCCP_HDR__

/**
 * struct dccp_hdr - generic part of DCCP packet header, with a 24-bit
 * sequence number
 *
 * @dccph_sport - Relevant port on the endpoint that sent this packet
 * @dccph_dport - Relevant port on the other endpoint
 * @dccph_doff - Data Offset from the start of the DCCP header, in 32-bit words
 * @dccph_ccval - Used by the HC-Sender CCID
 * @dccph_cscov - Parts of the packet that are covered by the Checksum field
 * @dccph_checksum - Internet checksum, depends on dccph_cscov
 * @dccph_x - 0 = 24 bit sequence number, 1 = 48
 * @dccph_type - packet type, see DCCP_PKT_ prefixed macros
 * @dccph_seq - 24-bit sequence number
 */
struct dccp_hdr {
	u_int16_t	dccph_sport,
			dccph_dport;
	u_int8_t	dccph_doff;
	u_int8_t	dccph_ccval_cscov;
	u_int16_t	dccph_checksum;
	u_int8_t	dccph_xtr;
	u_int8_t	dccph_seq[3];
} UNALIGNED;

/**
 * struct dccp_hdr_ext - generic part of DCCP packet header, with a 48-bit
 * sequence number
 *
 * @dccph_sport - Relevant port on the endpoint that sent this packet
 * @dccph_dport - Relevant port on the other endpoint
 * @dccph_doff - Data Offset from the start of the DCCP header, in 32-bit words
 * @dccph_ccval - Used by the HC-Sender CCID
 * @dccph_cscov - Parts of the packet that are covered by the Checksum field
 * @dccph_checksum - Internet checksum, depends on dccph_cscov
 * @dccph_x - 0 = 24 bit sequence number, 1 = 48
 * @dccph_type - packet type, see DCCP_PKT_ prefixed macros
 * @dccph_seq - 48-bit sequence number
 */
struct dccp_hdr_ext {
	u_int16_t	dccph_sport,
			dccph_dport;
	u_int8_t	dccph_doff;
	u_int8_t	dccph_ccval_cscov;
	u_int16_t	dccph_checksum;
	u_int8_t	dccph_xtr;
	u_int8_t	reserved;
	u_int8_t	dccph_seq[6];
} UNALIGNED;

#define DCCPH_CCVAL(dh)	(((dh)->dccph_ccval_cscov >> 4) & 0xF)
#define DCCPH_CSCOV(dh)	(((dh)->dccph_ccval_cscov) & 0xF)

#define DCCPH_X(dh)	((dh)->dccph_xtr & 1)
#define DCCPH_TYPE(dh)	(((dh)->dccph_xtr >> 1) & 0xF)

/**
 * struct dccp_hdr_request - Conection initiation request header
 *
 * @dccph_req_service - Service to which the client app wants to connect
 */
struct dccp_hdr_request {
	u_int32_t	dccph_req_service;
} UNALIGNED;

/**
 * struct dccp_hdr_response - Conection initiation response header
 *
 * @dccph_resp_ack - 48 bit ack number, contains GSR
 * @dccph_resp_service - Echoes the Service Code on a received DCCP-Request
 */
struct dccp_hdr_response {
	u_int8_t			dccph_resp_ack[8];	/* always 8 bytes */
	u_int32_t			dccph_resp_service;
} UNALIGNED;

/**
 * struct dccp_hdr_reset - Unconditionally shut down a connection
 *
 * @dccph_resp_ack - 48 bit ack number
 * @dccph_reset_service - Echoes the Service Code on a received DCCP-Request
 */
struct dccp_hdr_reset {
	u_int8_t			dccph_reset_ack[8];	/* always 8 bytes */
	u_int8_t			dccph_reset_code,
					dccph_reset_data[3];
} UNALIGNED;

enum dccp_pkt_type {
	DCCP_PKT_REQUEST = 0,
	DCCP_PKT_RESPONSE,
	DCCP_PKT_DATA,
	DCCP_PKT_ACK,
	DCCP_PKT_DATAACK,
	DCCP_PKT_CLOSEREQ,
	DCCP_PKT_CLOSE,
	DCCP_PKT_RESET,
	DCCP_PKT_SYNC,
	DCCP_PKT_SYNCACK,
	DCCP_PKT_INVALID
};

enum dccp_reset_codes {
	DCCP_RESET_CODE_UNSPECIFIED = 0,
	DCCP_RESET_CODE_CLOSED,
	DCCP_RESET_CODE_ABORTED,
	DCCP_RESET_CODE_NO_CONNECTION,
	DCCP_RESET_CODE_PACKET_ERROR,
	DCCP_RESET_CODE_OPTION_ERROR,
	DCCP_RESET_CODE_MANDATORY_ERROR,
	DCCP_RESET_CODE_CONNECTION_REFUSED,
	DCCP_RESET_CODE_BAD_SERVICE_CODE,
	DCCP_RESET_CODE_TOO_BUSY,
	DCCP_RESET_CODE_BAD_INIT_COOKIE,
	DCCP_RESET_CODE_AGGRESSION_PENALTY,
	__DCCP_RESET_CODE_LAST
};

#endif /* __DCCP_HDR__ */