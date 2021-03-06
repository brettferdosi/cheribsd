/*-
 * Copyright (c) 2014, 2016 Robert N. M. Watson
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
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
 */

/*
 * A few non-faulting CHERI-related virtual-memory tests.
 */

#include <sys/cdefs.h>

#if !__has_feature(capabilities)
#error "This code requires a CHERI-aware compiler"
#endif

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <sys/ucontext.h>
#include <sys/wait.h>

#include <sys/event.h>

#include <machine/frame.h>
#include <machine/trap.h>

#include <cheri/cheri.h>
#include <cheri/cheric.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#include "cheribsdtest.h"

static const char * xfail_need_writable_tmp(const char *name __unused);

/*
 * Tests to check that tags are ... or aren't ... preserved for various page
 * types.  'Anonymous' pages provided by the VM subsystem should always
 * preserve tags.  Pages from the filesystem should not -- unless they are
 * mapped MAP_PRIVATE, in which case they should, since they are effectively
 * anonymous pages.  Or so I claim.
 *
 * Most test cases only differ in the mmap flags and the file descriptor, this
 * function does all the shared checks
 */
static void
mmap_and_check_tag_stored(int fd, int protflags, int mapflags)
{
	void * __capability volatile *cp;
	void * __capability cp_value;
	int v;

	cp = CHERIBSDTEST_CHECK_SYSCALL(mmap(NULL, getpagesize(), protflags,
	     mapflags, fd, 0));
	cp_value = cheri_ptr(&v, sizeof(v));
	*cp = cp_value;
	cp_value = *cp;
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp_value) != 0, "tag lost");
	CHERIBSDTEST_CHECK_SYSCALL(munmap(__DEVOLATILE(void *, cp), getpagesize()));
	if (fd != -1)
		CHERIBSDTEST_CHECK_SYSCALL(close(fd));
}

CHERIBSDTEST(cheribsdtest_vm_tag_mmap_anon,
    "check tags are stored for MAP_ANON pages")
{
	mmap_and_check_tag_stored(-1, PROT_READ | PROT_WRITE, MAP_ANON);
	cheribsdtest_success();
}

CHERIBSDTEST(cheribsdtest_vm_tag_shm_open_anon_shared,
    "check tags are stored for SHM_ANON MAP_SHARED pages")
{
	int fd = CHERIBSDTEST_CHECK_SYSCALL(shm_open(SHM_ANON, O_RDWR, 0600));
	CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));
	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE, MAP_SHARED);
	cheribsdtest_success();
}

CHERIBSDTEST(cheribsdtest_vm_tag_shm_open_anon_private,
    "check tags are stored for SHM_ANON MAP_PRIVATE pages")
{
	int fd = CHERIBSDTEST_CHECK_SYSCALL(shm_open(SHM_ANON, O_RDWR, 0600));
	CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));
	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE, MAP_PRIVATE);
	cheribsdtest_success();
}

/*
 * Test aliasing of SHM_ANON objects
 */
CHERIBSDTEST(cheribsdtest_vm_tag_shm_open_anon_shared2x,
    "test multiply-mapped SHM_ANON objects")
{
	void * __capability volatile * map2;
	void * __capability c2;
	int fd = CHERIBSDTEST_CHECK_SYSCALL(shm_open(SHM_ANON, O_RDWR, 0600));
	CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));

	map2 = CHERIBSDTEST_CHECK_SYSCALL(mmap(NULL, getpagesize(),
		PROT_READ, MAP_SHARED, fd, 0));

	/* Verify that no capability present */
	c2 = *map2;
	CHERIBSDTEST_VERIFY2(cheri_gettag(c2) == 0, "tag exists on first read");
	CHERIBSDTEST_VERIFY2(c2 == NULL, "Initial read NULL");

	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE, MAP_SHARED);

	/* And now verify that it is, thanks to the aliased maps */
	c2 = *map2;
	CHERIBSDTEST_VERIFY2(cheri_gettag(c2) != 0, "tag lost on second read");
	CHERIBSDTEST_VERIFY2(c2 != NULL, "Second read not NULL");

	cheribsdtest_success();
}

CHERIBSDTEST(cheribsdtest_vm_shm_open_anon_unix_surprise,
    "test SHM_ANON vs SCM_RIGHTS",
    .ct_xfail_reason =
	"Tags currently survive cross-AS aliasing of SHM_ANON objects")
{
	int sv[2];
	int pid;

	CHERIBSDTEST_CHECK_SYSCALL(socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) != 0);

	pid = fork();
	if (pid == -1)
		cheribsdtest_failure_errx("Fork failed; errno=%d", errno);

	if (pid == 0) {
		void * __capability * map;
		void * __capability c;
		int fd, tag;
		struct msghdr msg = { 0 };
		struct cmsghdr * cmsg;
		char cmsgbuf[CMSG_SPACE(sizeof(fd))] = { 0 } ;
		char iovbuf[16];
		struct iovec iov = { .iov_base = iovbuf, .iov_len = sizeof(iovbuf) };

		close(sv[1]);

		/* Read from socket */
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = cmsgbuf;
		msg.msg_controllen = sizeof(cmsgbuf);
		CHERIBSDTEST_CHECK_SYSCALL(recvmsg(sv[0], &msg, 0));

		/* Deconstruct cmsg */
		/* XXX Doesn't compile: cmsg = CMSG_FIRSTHDR(&msg); */
		cmsg = msg.msg_control;
		memmove(&fd, CMSG_DATA(cmsg), sizeof(fd));

		CHERIBSDTEST_VERIFY2(fd >= 0, "fd read OK");

		map = CHERIBSDTEST_CHECK_SYSCALL(mmap(NULL, getpagesize(),
						PROT_READ, MAP_SHARED, fd,
						0));
		c = *map;

		fprintf(stderr, "rx cap: v:%lu b:%016jx l:%016zx o:%jx\n",
			(unsigned long)cheri_gettag(c), cheri_getbase(c),
			cheri_getlen(c), cheri_getoffset(c));

		tag = cheri_gettag(c);
		CHERIBSDTEST_VERIFY2(tag == 0, "tag read");

		CHERIBSDTEST_CHECK_SYSCALL(munmap(map, getpagesize()));
		close(sv[0]);
		close(fd);

		exit(tag);
	} else {
		void * __capability * map;
		void * __capability c;
		int fd, res;
		struct msghdr msg = { 0 };
		struct cmsghdr * cmsg;
		char cmsgbuf[CMSG_SPACE(sizeof(fd))] = { 0 };
		char iovbuf[16] = { 0 };
		struct iovec iov = { .iov_base = iovbuf, .iov_len = sizeof(iovbuf) };

		close(sv[0]);

		fd = CHERIBSDTEST_CHECK_SYSCALL(shm_open(SHM_ANON, O_RDWR, 0600));
		CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));

		map = CHERIBSDTEST_CHECK_SYSCALL(mmap(NULL, getpagesize(),
						PROT_READ | PROT_WRITE,
						MAP_SHARED, fd, 0));

		/* Just some pointer */
		*map = &fd;
		c = *map;
		CHERIBSDTEST_VERIFY2(cheri_gettag(c) != 0, "tag written");

		fprintf(stderr, "tx cap: v:%lu b:%016jx l:%016zx o:%jx\n",
			(unsigned long)cheri_gettag(c), cheri_getbase(c),
			cheri_getlen(c), cheri_getoffset(c));

		CHERIBSDTEST_CHECK_SYSCALL(munmap(map, getpagesize()));

		/* Construct control message */
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		msg.msg_control = cmsgbuf;
		msg.msg_controllen = sizeof(cmsgbuf);
		/* XXX cmsg = CMSG_FIRSTHDR(&msg); */
		cmsg = msg.msg_control;
		cmsg->cmsg_level = SOL_SOCKET;
		cmsg->cmsg_type = SCM_RIGHTS;
		cmsg->cmsg_len = CMSG_LEN(sizeof fd);
		memmove(CMSG_DATA(cmsg), &fd, sizeof(fd));
		msg.msg_controllen = cmsg->cmsg_len;

		/* Send! */
		CHERIBSDTEST_CHECK_SYSCALL(sendmsg(sv[1], &msg, 0));

		close(sv[1]);
		close(fd);

		waitpid(pid, &res, 0);
		if (res == 0) {
			cheribsdtest_success();
		} else {
			cheribsdtest_failure_errx("tag transfer succeeded");
		}
	}
}

#ifdef __CHERI_PURE_CAPABILITY__

/*
 * We can fork processes with shared file descriptor tables, including
 * shared access to a kqueue, which can hoard capabilities for us, allowing
 * them to flow between address spaces.  It is difficult to know what to do
 * about this case, but it seems important to acknowledge.
 */
CHERIBSDTEST(cheribsdtest_vm_cap_share_fd_kqueue,
    "Demonstrate capability passing via shared FD table",
    .ct_xfail_reason = "Tags currently survive cross-AS shared FD tables")
{
	int kq, pid;

	kq = CHERIBSDTEST_CHECK_SYSCALL(kqueue());
	pid = rfork(RFPROC);
	if (pid == -1)
		cheribsdtest_failure_errx("Fork failed; errno=%d", errno);

	if (pid == 0) {
		struct kevent oke;
		/*
		 * Wait for receipt of the user event, and witness the
		 * capability received from the parent.
		 */
		oke.udata = NULL;
		CHERIBSDTEST_CHECK_SYSCALL(kevent(kq, NULL, 0, &oke, 1, NULL));
		CHERIBSDTEST_VERIFY2(oke.ident == 0x2BAD, "Bad identifier from kqueue");
		CHERIBSDTEST_VERIFY2(oke.filter == EVFILT_USER, "Bad filter from kqueue");

		fprintf(stderr, "oke.udata %#lp\n", oke.udata);

		exit(cheri_gettag(oke.udata));
	} else {
		int res;
		struct kevent ike;
		void * __capability passme;

		/*
		 * Generate a capability to a new mapping to pass to the
		 * child, who will not have this region mapped.
		 */
		passme = CHERIBSDTEST_CHECK_SYSCALL(mmap(0, PAGE_SIZE,
				PROT_READ | PROT_WRITE, MAP_ANON, -1, 0));

		EV_SET(&ike, 0x2BAD, EVFILT_USER, EV_ADD|EV_ONESHOT,
			NOTE_FFNOP, 0, passme);
		CHERIBSDTEST_CHECK_SYSCALL(kevent(kq, &ike, 1, NULL, 0, NULL));

		EV_SET(&ike, 0x2BAD, EVFILT_USER, EV_KEEPUDATA,
			NOTE_FFNOP|NOTE_TRIGGER, 0, NULL);
		CHERIBSDTEST_CHECK_SYSCALL(kevent(kq, &ike, 1, NULL, 0, NULL));

		waitpid(pid, &res, 0);
		if (res == 0) {
			cheribsdtest_success();
		} else {
			cheribsdtest_failure_errx("tag transfer");
		}
	}
}

extern int __sys_sigaction(int, const struct sigaction *, struct sigaction *);

/*
 * We can rfork and share the sigaction table across parent and child, which
 * again allows for capability passing across address spaces.
 */
CHERIBSDTEST(cheribsdtest_vm_cap_share_sigaction,
    "Demonstrate capability passing via shared sigaction table",
    .ct_xfail_reason = "Tags currently survive cross-AS shared sigaction table")
{
	int pid;

	pid = rfork(RFPROC | RFSIGSHARE);
	if (pid == -1)
		cheribsdtest_failure_errx("Fork failed; errno=%d", errno);

	/*
	 * Note: we call __sys_sigaction directly here, since the libthr
	 * _thr_sigaction has a shadow list for the sigaction values
	 * (per-process) and therefore does not read the new value installed by
	 * the child process forked with RFSIGSHARE.
	 */
	if (pid == 0) {
		void *__capability passme;
		struct sigaction sa;

		bzero(&sa, sizeof(sa));

		/* This is a little abusive, but shows the point, I think */

		passme = CHERIBSDTEST_CHECK_SYSCALL(mmap(0, PAGE_SIZE,
		    PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON, -1, 0));
		sa.sa_handler = passme;

		CHERIBSDTEST_CHECK_SYSCALL(__sys_sigaction(SIGUSR1, &sa, NULL));

		/* Read it again and check that we get the same value back. */
		CHERIBSDTEST_CHECK_SYSCALL(__sys_sigaction(SIGUSR1, NULL, &sa));
		fprintf(stderr, "child value read from sigaction(): ");
		fprintf(stderr, "sa.sa_handler %#lp\n", sa.sa_handler);
		CHERIBSDTEST_CHECK_EQ_CAP(sa.sa_handler, passme);

		exit(0);
	} else {
		struct sigaction sa;

		waitpid(pid, NULL, 0);

		bzero(&sa, sizeof(sa));
		sa.sa_flags = 1;

		CHERIBSDTEST_CHECK_SYSCALL(__sys_sigaction(SIGUSR1, NULL, &sa));
		fprintf(stderr, "parent sa read from sigaction(): ");
		fprintf(stderr, "sa.sa_handler %#lp\n", sa.sa_handler);

		/* Flags should be zero on read */
		CHERIBSDTEST_CHECK_EQ_LONG(sa.sa_flags, 0);

		if (cheri_gettag(sa.sa_handler)) {
			cheribsdtest_failure_errx("tag transfer");
		} else {
			cheribsdtest_success();
		}
	}
}

#endif

CHERIBSDTEST(cheribsdtest_vm_tag_dev_zero_shared,
    "check tags are stored for /dev/zero MAP_SHARED pages")
{
	int fd = CHERIBSDTEST_CHECK_SYSCALL(open("/dev/zero", O_RDWR));
	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE, MAP_SHARED);
	cheribsdtest_success();
}

CHERIBSDTEST(cheribsdtest_vm_tag_dev_zero_private,
    "check tags are stored for /dev/zero MAP_PRIVATE pages")
{
	int fd = CHERIBSDTEST_CHECK_SYSCALL(open("/dev/zero", O_RDWR));
	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE, MAP_PRIVATE);
	cheribsdtest_success();
}

static int
create_tempfile()
{
	char template[] = "/tmp/cheribsdtest.XXXXXXXX";
	int fd = CHERIBSDTEST_CHECK_SYSCALL2(mkstemp(template),
	    "mkstemp %s", template);
	CHERIBSDTEST_CHECK_SYSCALL(unlink(template));
	CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));
	return fd;
}

/*
 * This case should fault.
 * XXXRW: I wonder if we also need some sort of load-related test?
 */
CHERIBSDTEST(cheribsdtest_vm_notag_tmpfile_shared,
    "check tags are not stored for tmpfile() MAP_SHARED pages",
    .ct_flags = CT_FLAG_SIGNAL | CT_FLAG_SI_CODE | CT_FLAG_SI_TRAPNO,
    .ct_signum = SIGSEGV,
    .ct_si_code = SEGV_STORETAG,
    .ct_si_trapno = TRAPNO_STORE_CAP_PF,
    .ct_check_xfail = xfail_need_writable_tmp)
{
	void * __capability volatile *cp;
	void * __capability cp_value;
	int fd, v;

	fd = create_tempfile();
	cp = CHERIBSDTEST_CHECK_SYSCALL(mmap(NULL, getpagesize(),
	    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
	cp_value = cheri_ptr(&v, sizeof(v));
	*cp = cp_value;
	cheribsdtest_failure_errx("tagged store succeeded");
}

CHERIBSDTEST(cheribsdtest_vm_tag_tmpfile_private,
    "check tags are stored for tmpfile() MAP_PRIVATE pages",
    .ct_check_xfail = xfail_need_writable_tmp)
{
	int fd = create_tempfile();
	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE, MAP_PRIVATE);
	cheribsdtest_success();
}

CHERIBSDTEST(cheribsdtest_vm_tag_tmpfile_private_prefault,
    "check tags are stored for tmpfile() MAP_PRIVATE, MAP_PREFAULT_READ pages",
    .ct_check_xfail = xfail_need_writable_tmp)
{
	int fd = create_tempfile();
	mmap_and_check_tag_stored(fd, PROT_READ | PROT_WRITE,
	    MAP_PRIVATE | MAP_PREFAULT_READ);
	cheribsdtest_success();
}

static const char *
xfail_need_writable_tmp(const char *name __unused)
{
	static const char *reason = NULL;
	static int checked = 0;
	char template[] = "/tmp/cheribsdtest.XXXXXXXX";
	int fd;

	if (checked)
		return (reason);

	checked = 1;
	fd = mkstemp(template);
	if (fd >= 0) {
		close(fd);
		unlink(template);
		return (NULL);
	}
	reason = "/tmp is not writable";
	return (reason);
}

/*
 * Exercise copy-on-write:
 *
 * 1) Create a new anonymous shared memory object, extend to page size, map,
 * and write a tagged capability to it.
 *
 * 2) Create a second copy-on-write mapping; read back the tagged value via
 * the second mapping, and confirm that it still has a tag.
 * (cheribsdtest_vm_cow_read)
 *
 * 3) Write an adjacent word in the second mapping, which should cause a
 * copy-on-write, then read back the capability and confirm that it still has
 * a tag.  (cheribsdtest_vm_cow_write)
 */
CHERIBSDTEST(cheribsdtest_vm_cow_read,
    "read capabilities from a copy-on-write page")
{
	void * __capability volatile *cp_copy;
	void * __capability volatile *cp_real;
	void * __capability cp;
	int fd;

	/*
	 * Create anonymous shared memory object.
	 */
	fd = CHERIBSDTEST_CHECK_SYSCALL(shm_open(SHM_ANON, O_RDWR, 0600));
	CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));

	/*
	 * Create 'real' and copy-on-write mappings.
	 */
	cp_real = CHERIBSDTEST_CHECK_SYSCALL2(mmap(NULL, getpagesize(),
	    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0), "mmap cp_real");
	cp_copy = CHERIBSDTEST_CHECK_SYSCALL2(mmap(NULL, getpagesize(),
	    PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0), "mmap cp_copy");

	/*
	 * Write out a tagged capability to 'real' mapping -- doesn't really
	 * matter what it points at.  Confirm it has a tag.
	 */
	cp = cheri_ptr(&fd, sizeof(fd));
	cp_real[0] = cp;
	cp = cp_real[0];
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp) != 0, "pretest: tag missing");

	/*
	 * Read in tagged capability via copy-on-write mapping.  Confirm it
	 * has a tag.
	 */
	cp = cp_copy[0];
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp) != 0, "tag missing, cp_real");

	/*
	 * Clean up.
	 */
	CHERIBSDTEST_CHECK_SYSCALL2(munmap(__DEVOLATILE(void *, cp_real),
	    getpagesize()), "munmap cp_real");
	CHERIBSDTEST_CHECK_SYSCALL2(munmap(__DEVOLATILE(void *, cp_copy),
	    getpagesize()), "munmap cp_copy");
	CHERIBSDTEST_CHECK_SYSCALL(close(fd));
	cheribsdtest_success();
}

CHERIBSDTEST(cheribsdtest_vm_cow_write,
    "read capabilities from a faulted copy-on-write page")
{
	void * __capability volatile *cp_copy;
	void * __capability volatile *cp_real;
	void * __capability cp;
	int fd;

	/*
	 * Create anonymous shared memory object.
	 */
	fd = CHERIBSDTEST_CHECK_SYSCALL(shm_open(SHM_ANON, O_RDWR, 0600));
	CHERIBSDTEST_CHECK_SYSCALL(ftruncate(fd, getpagesize()));

	/*
	 * Create 'real' and copy-on-write mappings.
	 */
	cp_real = CHERIBSDTEST_CHECK_SYSCALL2(mmap(NULL, getpagesize(),
	    PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0), "mmap cp_real");
	cp_copy = CHERIBSDTEST_CHECK_SYSCALL2(mmap(NULL, getpagesize(),
	    PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0), "mmap cp_copy");

	/*
	 * Write out a tagged capability to 'real' mapping -- doesn't really
	 * matter what it points at.  Confirm it has a tag.
	 */
	cp = cheri_ptr(&fd, sizeof(fd));
	cp_real[0] = cp;
	cp = cp_real[0];
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp) != 0, "pretest: tag missing");

	/*
	 * Read in tagged capability via copy-on-write mapping.  Confirm it
	 * has a tag.
	 */
	cp = cp_copy[0];
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp) != 0, "tag missing, cp_real");

	/*
	 * Diverge from cheribsdtest_vm_cow_read(): write via the second mapping
	 * to force a copy-on-write rather than continued sharing of the page.
	 */
	cp = cheri_ptr(&fd, sizeof(fd));
	cp_copy[1] = cp;

	/*
	 * Confirm that the tag is still present on the 'real' page.
	 */
	cp = cp_real[0];
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp) != 0, "tag missing after COW, cp_real");

	cp = cp_copy[0];
	CHERIBSDTEST_VERIFY2(cheri_gettag(cp) != 0, "tag missing after COW, cp_copy");

	/*
	 * Clean up.
	 */
	CHERIBSDTEST_CHECK_SYSCALL2(munmap(__DEVOLATILE(void *, cp_real),
	    getpagesize()), "munmap cp_real");
	CHERIBSDTEST_CHECK_SYSCALL2(munmap(__DEVOLATILE(void *, cp_copy),
	    getpagesize()), "munmap cp_copy");
	CHERIBSDTEST_CHECK_SYSCALL(close(fd));
	cheribsdtest_success();
}
