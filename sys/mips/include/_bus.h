/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2005 M. Warner Losh <imp@FreeBSD.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification, immediately at the beginning of the file.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * from: src/sys/i386/include/_bus.h,v 1.1 2005/04/18 21:45:33 imp
 * $FreeBSD$
 */

#ifndef MIPS_INCLUDE__BUS_H
#define	MIPS_INCLUDE__BUS_H

/*
 * Bus address and size types
 */

/*
 * bus_addr_t: an address in the bus space.
 * bus_size_t: size of objects in the bus space.
 */
typedef vm_paddr_t bus_addr_t;
typedef vm_size_t bus_size_t;

/*
 * Access methods for bus resources and address space.
 */
typedef struct bus_space *bus_space_tag_t;
#ifdef __CHERI_PURE_CAPABILITY__
/*
 * With CHERI, the bus space handle is a capability to a mapped
 * bus space memory object.
 */
typedef uintptr_t bus_space_handle_t;
#else /* ! __CHERI_PURE_CAPABILITY__ */
typedef bus_addr_t bus_space_handle_t;
#endif /* ! __CHERI_PURE_CAPABILITY__ */
#endif /* MIPS_INCLUDE__BUS_H */

// CHERI CHANGES START
// {
//   "updated": 20201230,
//   "target_type": "header",
//   "changes_purecap": [
//     "pointer_as_integer"
//   ]
// }
// CHERI CHANGES END
