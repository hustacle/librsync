/* -*- mode: c; c-file-style: "bsd" -*- */
/* -------------------------------------------------------------------
 * $Id$
 *
 * gdproto.c -- The on-the-wire gd01 protocol.
 *
   Copyright (C) 1999-2000 by Martin Pool.
   
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free 
   Software Foundation; either version 2 of the License, or (at your option)
   any later version.
   
   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.
   
   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc., 59 
   Temple Place, Suite 330, Boston, MA 02111-1307 USA 
  */

#include "includes.h"

int
_hs_read_blocksize(hs_read_fn_t sigread_fn, void *sigreadprivate,
		   int *block_len)
{
     int ret;

     ret = _hs_read_netint(sigread_fn, sigreadprivate, block_len);
     if (ret < 0) {
	  _hs_error("couldn't read block length from signature");
	  return -1;
     } else if (ret != 4) {
	  _hs_error("short read while trying to get block length");
	  return -1;
     }

     _hs_trace("The block length is %d", *block_len);

     return 0;
}



int
_hs_littok_header(hs_write_fn_t write_fn, void *write_priv)
{
     int ret;

     /*
      * Write the protocol version the token stream follows to the token
      * stream 
      */
     ret = _hs_write_netint(write_fn, write_priv, HS_LT_MAGIC);
     if (ret < 0) {
	  _hs_fatal("error writing version to littok stream");
	  return -1;
     }

     return 0;
}



int
_hs_check_sig_version(hs_read_fn_t sigread_fn, void *sigreadprivate)
{
     uint32_t hs_remote_version;
     const uint32_t expect = HS_SIG_MAGIC;
     int ret;

     ret = _hs_read_netint(sigread_fn, sigreadprivate, &hs_remote_version);
     if (ret == 0) {
	  _hs_trace("eof on old signature stream before reading version; "
		    "there is no old signature");
	  return 0;
     } else if (ret < 0) {
	  _hs_fatal("error reading signature version");
	  return -1;
     } else if (ret != 4) {
	  _hs_fatal("bad-sized read while trying to get signature version");
	  return -1;
     }

     if (hs_remote_version != expect) {
	  _hs_fatal("this librsync understands version %#010x."
		    " We don't take %#010x.", expect, hs_remote_version);
	  errno = EBADMSG;
	  return -1;
     }

     return 1;
}

int
_hs_newsig_header(int new_block_len,
		  hs_write_fn_t write_fn, void *writeprivate)
{
     int ret;
     ret = _hs_write_netint(write_fn, writeprivate, HS_SIG_MAGIC);
     if (ret < 0)
	  return -1;

     ret = _hs_write_netint(write_fn, writeprivate, new_block_len);
     if (ret < 0)
	  return -1;

     return 0;
}



/* Read and remember all the signatures from last time. */
int
_hs_read_sums(hs_encode_job_t *job,
	      hs_read_fn_t sigread_fn, void *sigread_priv)
{
    int ret;
    int block_len;
    
    ret = _hs_check_sig_version(sigread_fn, sigread_priv);
    job->got_old = (ret > 0);
    if (!job->got_old)
	return 0;

    if (_hs_read_blocksize(sigread_fn, sigread_priv, &block_len) < 0)
	return job->got_old = 0;

    job->sums = _hs_read_sum_set(sigread_fn, sigread_priv, block_len);
    if (!job->sums) 
	return job->got_old = 0;

    return 1;
}

