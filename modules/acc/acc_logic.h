/*
 * Accounting module
 *
 * Copyright (C) 2006 Voice Sistem SRL
 *
 * This file is part of opensips, a free SIP server.
 *
 * opensips is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * opensips is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * History:
 * ---------
 * 2005-09-19  created during a big re-structuring of acc module(bogdan)
 */


#ifndef _ACC_ACC_LOGIC_H
#define _ACC_ACC_LOGIC_H

#include "../../str.h"
#include "../tm/t_hooks.h"
#include "../dialog/dlg_cb.h"

#define DO_ACC_LOG  (1<<(0*8))
#define DO_ACC_AAA  (1<<(1*8))
#define DO_ACC_DB   (1<<(2*8))
#define DO_ACC_DIAM (1<<(3*8))
#define DO_ACC_EVI  ((unsigned long long)1<<(4*8))

#define DO_ACC        (1<<0) /* generic accouting flag - internal only */
#define DO_ACC_CDR    (1<<1)
#define DO_ACC_MISSED (1<<2)
#define DO_ACC_FAILED (1<<3)

#define DO_ACC_PARAM_TYPE_PV    (1<<0)
#define DO_ACC_PARAM_TYPE_VALUE (1<<1)

#define DO_ACC_LOG_STR  "log"
#define DO_ACC_AAA_STR  "aaa"
#define DO_ACC_DB_STR   "db"
#define DO_ACC_DIAM_STR "diam"
#define DO_ACC_EVI_STR  "evi"

#define DO_ACC_CDR_STR    "cdr"
#define DO_ACC_MISSED_STR "missed"
#define DO_ACC_FAILED_STR "failed"

#define DO_ACC_PARAM_DELIMITER '|'

typedef unsigned long long (*do_acc_parser)(str*);

typedef struct acc_type_param {
	int t;
	union {
		unsigned long long ival;
		pv_elem_p pval;
	} u;
} acc_type_param_t;

/* various acc variables */
struct acc_enviroment {
	unsigned int code;
	str code_s;
	str reason;
	struct hdr_field *to;
	str text;
	struct timeval ts;
  event_id_t event;
};

/* param trasnporter*/
struct acc_param {
	int code;
	str code_s;
	str reason;
};


void acc_onreq( struct cell* t, int type, struct tmcb_params *ps );

int w_acc_log_request(struct sip_msg *rq, pv_elem_t* comment, char *foo);

int w_acc_aaa_request(struct sip_msg *rq, pv_elem_t* comment, char *foo);

int w_acc_db_request(struct sip_msg *rq, pv_elem_t* comment, char *table);

int acc_pvel_to_acc_param(struct sip_msg *rq, pv_elem_t* pv_el, struct acc_param* accp);

void acc_loaded_callback(struct dlg_cell *dlg, int type,
			struct dlg_cb_params *_params);

#ifdef DIAM_ACC
int w_acc_diam_request(struct sip_msg *rq, char *comment, char *foo);
#endif

int w_acc_evi_request(struct sip_msg *rq, pv_elem_t* comment, char *foo);


int do_acc_fixup(void** param, int param_no);


int w_do_acc_1(struct sip_msg* msg, char* type);
int w_do_acc_2(struct sip_msg* msg, char* type, char* flags);
int w_do_acc_3(struct sip_msg* msg, char* type_p, char* flags_p, char* table_p);

#endif
