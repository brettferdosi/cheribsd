/*-
 * SPDX-License-Identifier: BSD-4-Clause
 *
 * Copyright 1996-1998 John D. Polstra.
 * All rights reserved.
 * Copyright (c) 1995 Christopher G. Demetriou
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Christopher G. Demetriou
 *    for the NetBSD Project.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <stdlib.h>
#include "libc_private.h"
#include "ignore_init.c"

struct Struct_Obj_Entry;
struct ps_strings;

#ifdef GCRT
extern void _mcleanup(void);
extern void monstartup(void *, void *);
extern int eprol;
extern int etext;
#endif

/*
 * For -pie executables rtld will process capability relocations, so we don't
 * need to include the code here.
 */
#if __has_feature(capabilities) && !defined(PIC)
#define SHOULD_PROCESS_CAP_RELOCS
#endif

#ifdef SHOULD_PROCESS_CAP_RELOCS
#define DONT_EXPORT_CRT_INIT_GLOBALS
#define CRT_INIT_GLOBALS_GDC_ONLY
#include "crt_init_globals.c"
#endif

void __start(char **, void (*)(void), struct Struct_Obj_Entry *, struct ps_strings *);

/* The entry function. */
void
__start(char **ap,
	void (*cleanup)(void),			/* from shared loader */
	struct Struct_Obj_Entry *obj __unused,	/* from shared loader */
	struct ps_strings *ps_strings __unused)
{
	int argc;
	char **argv;
	char **env;

	argc = * (long *) ap;
	argv = ap + 1;
	env  = ap + 2 + argc;

#ifdef SHOULD_PROCESS_CAP_RELOCS
	/*
	 * Initialize __cap_relocs for static executables. The run-time linker
	 * will initialise any for dynamic executables.
	 */
	if (&_DYNAMIC == NULL) {
		const Elf_Auxinfo *auxp;
		char **strp;
		void *phdr = NULL;
		long phnum = 0;

		strp = env;
		while (*strp++ != NULL)
			;
		auxp = (Elf_Auxinfo *)strp;

		for (; auxp->a_type != AT_NULL; auxp++) {
			if (auxp->a_type == AT_PHDR) {
				phdr = auxp->a_un.a_ptr;
			} else if (auxp->a_type == AT_PHNUM) {
				phnum = auxp->a_un.a_val;
			}
		}

		if (phdr != NULL && phnum != 0) {
			do_crt_init_globals(phdr, phnum);
		}
	}
#endif

	handle_argv(argc, argv, env);

	if (&_DYNAMIC != NULL)
		atexit(cleanup);
	else
		_init_tls();

#ifdef GCRT
	atexit(_mcleanup);
	monstartup(&eprol, &etext);
#endif

	handle_static_init(argc, argv, env);
	exit(main(argc, argv, env));
}

#ifdef GCRT
__asm__(".text");
__asm__("eprol:");
__asm__(".previous");
#endif
