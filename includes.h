/* -*- mode: c; c-file-style: "bsd" -*-  */
/* $Id$ */
/* libhsync/includes.h -- All system and application headers
   
   Copyright (C) 2000 by Martin Pool <mbp@humbug.org.au>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
   USA
*/

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/file.h>
#ifndef __LCLINT__
/* This contains GCC-specific stuff that confuses lclint */
#include <netinet/in.h>		/* ntohs, etc */
#endif /* __LCLINT__ */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


/* libhsync headers. */
#include "hsync.h"
#include "hsyncproto.h"
#include "private.h"
#include "emit.h"
#include "util.h"
#include "gd02priv.h"
