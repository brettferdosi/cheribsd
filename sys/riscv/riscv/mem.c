/*-
 * Copyright (c) 2014 Andrew Turner
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/malloc.h>
#include <sys/memrange.h>
#include <sys/uio.h>

#include <machine/memdev.h>
#include <machine/vmparam.h>

#include <vm/vm.h>
#include <vm/pmap.h>
#include <vm/vm_extern.h>
#include <vm/vm_page.h>

#ifdef __CHERI_PURE_CAPABILITY__
#include <cheri/cheric.h>
#endif

struct mem_range_softc mem_range_softc;

int
memrw(struct cdev *dev, struct uio *uio, int flags)
{
	ssize_t orig_resid;
	vm_offset_t off, v;
	struct iovec *iov;
	struct vm_page m;
	vm_page_t marr;
	u_int cnt;
	int error;

	error = 0;
	orig_resid = uio->uio_resid;
	while (uio->uio_resid > 0 && error == 0) {
		iov = uio->uio_iov;
		if (iov->iov_len == 0) {
			uio->uio_iov++;
			uio->uio_iovcnt--;
			if (uio->uio_iovcnt < 0)
				panic("memrw");
			continue;
		}

		v = uio->uio_offset;
		off = v & PAGE_MASK;
		cnt = ulmin(iov->iov_len, PAGE_SIZE - (u_int)off);
		if (cnt == 0)
			continue;

		switch(dev2unit(dev)) {
		case CDEV_MINOR_KMEM:
			/* If the address is in the DMAP just copy it */
			if (VIRT_IN_DMAP(v)) {
#ifdef __CHERI_PURE_CAPABILITY__
				error = uiomove(cheri_setbounds(
				    cheri_setaddress(dmap_capability, v), cnt),
				    cnt, uio);
#else
				error = uiomove((void *)v, cnt, uio);
#endif
				break;
			}

			if (!kernacc((void *)(uintptr_t)v, cnt, uio->uio_rw ==
			    UIO_READ ? VM_PROT_READ : VM_PROT_WRITE)) {
				error = EFAULT;
				break;
			}

			/* Get the physical address to read */
			v = pmap_extract(kernel_pmap, v);
			if (v == 0) {
				error = EFAULT;
				break;
			}

			/* FALLTHROUGH */
		case CDEV_MINOR_MEM:
			/* If within the DMAP use this to copy from */
			if (PHYS_IN_DMAP(v)) {
#ifdef __CHERI_PURE_CAPABILITY__
				error = uiomove(cheri_setbounds(
				    (void *)PHYS_TO_DMAP(v), cnt), cnt, uio);
#else
				v = PHYS_TO_DMAP(v);
				error = uiomove((void *)v, cnt, uio);
#endif
				break;
			}

			/* Have uiomove_fromphys handle the data */
			m.phys_addr = trunc_page(v);
			marr = &m;
			uiomove_fromphys(&marr, off, cnt, uio);
			break;
		}
	}

	/*
	 * Don't return error if any byte was written.  Read and write
	 * can return error only if no i/o was performed.
	 */
	if (uio->uio_resid != orig_resid)
		error = 0;

	return (error);
}

/*
 * Allow user processes to MMAP some memory sections
 * instead of going through read/write.
 */
int
memmmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot __unused, vm_memattr_t *memattr __unused)
{
	if (dev2unit(dev) == CDEV_MINOR_MEM) {
		*paddr = offset;
		return (0);
	}
	return (-1);
}

int
memioctl_md(struct cdev *dev __unused, u_long cmd __unused,
    caddr_t data __unused, int flags __unused, struct thread *td __unused)
{
	return (ENOTTY);
}
// CHERI CHANGES START
// {
//   "updated": 20200803,
//   "target_type": "kernel",
//   "changes_purecap": [
//     "pointer_as_integer"
//   ]
// }
// CHERI CHANGES END
