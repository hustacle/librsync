## Process this file with automake to produce Makefile.in

# Copyright (C) 2000, 2001, 2002, 2014 by Martin Pool <mbp@sourcefrog.net>
# Copyright (C) 2003 by Donovan Baarda <abo@minkirri.apana.org.au> 

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public License
# as published by the Free Software Foundation; either version 2.1 of
# the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

AUTOMAKE_OPTIONS = foreign
SUBDIRS = . doc testsuite
ACLOCAL_AMFLAGS = -I m4

MAINTAINERCLEANFILES = Makefile.in \
	aclocal.m4 config.guess config.h.in config.sub configure \
	depcomp install-sh ltmain.sh missing mkinstalldirs \
	prototab.c prototab.h

EXTRA_DIST = autogen.sh configure.msc $(noinst_SCRIPTS) rdiff.magic \
	librsync.spec README.RPM libversions.txt \
	PCbuild/rdiff.dsp PCbuild/PCbuild.dsw   PCbuild/config.h \
	PCbuild/librsync-config.h

include_HEADERS = librsync.h librsync-config.h

lib_LTLIBRARIES = librsync.la

librsync_la_SOURCES =  prototab.c prototab.h \
	base64.c buf.c buf.h checksum.c checksum.h command.c \
	command.h delta.c emit.c emit.h fileutil.c fileutil.h \
	hex.c job.c job.h mdfour.c mdfour.h mksum.c msg.c netint.c netint.h \
	patch.c readsums.c librsync.h librsync-config.h \
	rollsum.c rollsum.h \
	scoop.c search.c search.h stats.c stream.c stream.h sumset.c \
	sumset.h trace.c trace.h tube.c types.h util.c util.h \
	version.c whole.c whole.h snprintf.h \
	blake2b-ref.c blake2.h blake2-impl.h

librsync_la_LIBADD = @LIBOBJS@

librsync_la_LDFLAGS = -version-info @librsync_libversion@

# This is the default for any programs that don't specify a preference.
LDADD = librsync.la

# This is the rdiff application
bin_PROGRAMS = rdiff

rdiff_SOURCES = rdiff.c isprefix.c isprefix.h librsync.h librsync-config.h \
	trace.h

rdiff_LDADD = librsync.la

rdiff_DEPENDENCIES = librsync.la

# this script is used to build prototab.[ch]
noinst_SCRIPTS = mkprototab.pl

# Autogenerated by a script.
prototab.c prototab.h: $(srcdir)/mkprototab.pl
	perl $(srcdir)/mkprototab.pl prototab.c prototab.h
