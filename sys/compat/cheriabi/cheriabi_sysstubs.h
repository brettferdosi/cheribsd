/*
 * System call stub generation macros.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 * created from FreeBSD
 */

#include <sys/acl.h>
#include <sys/cpuset.h>
#include <sys/_ffcounter.h>
#include <sys/_semaphore.h>
#include <sys/socket.h>
#include <sys/ucontext.h>
#include <compat/cheriabi/cheriabi_signal.h>
#if !defined(PAD64_REQUIRED) && (defined(__powerpc__) || defined(__mips__))
#define PAD64_REQUIRED
#endif
struct __wrusage;
struct acl;
struct aiocb;
struct auditinfo;
struct auditinfo_addr;
struct chericap;
struct ffclock_estimate;
struct fhandle;
struct iovec;
struct itimerspec;
struct itimerval;
struct jail;
struct kevent;
struct kld_file_stat;
struct kld_sym_lookup;
struct mac;
struct module_stat;
struct mq_attr;
struct msghdr;
struct msqid_ds;
struct nstat;
struct ntptimeval;
struct pollfd;
struct rlimit;
struct rtprio;
struct rusage;
struct sched_param;
struct sctp_sndrcvinfo;
struct sembuf;
struct sf_hdtr;
struct shmid_ds;
struct sigaction;
struct sigevent;
struct siginfo;
struct sockaddr;
struct stat;
struct statfs;
struct thr_param;
struct timespec;
struct timeval;
struct timex;
struct timezone;
struct uuid;
struct vm_domain_policy_entry;
union semun;
SYS_STUB(2, int, fork, (void), ());
SYS_STUB(3, ssize_t, read, (int fd, void * buf, size_t nbyte), (fd, buf, nbyte));
SYS_STUB(4, ssize_t, write, (int fd, const void * buf, size_t nbyte), (fd, buf, nbyte));
SYS_STUB_VA(5, int, open, (const char * path, int flags, ...), (const char * path, int flags, va_list ap), (path, flags, ap), flags);
SYS_STUB(6, int, close, (int fd), (fd));
SYS_STUB(7, int, wait4, (int pid, int * status, int options, struct rusage * rusage), (pid, status, options, rusage));
SYS_STUB(9, int, link, (const char * path, const char * to), (path, to));
SYS_STUB(10, int, unlink, (const char * path), (path));
SYS_STUB(12, int, chdir, (const char * path), (path));
SYS_STUB(13, int, fchdir, (int fd), (fd));
SYS_STUB(14, int, mknod, (const char * path, mode_t mode, dev_t dev), (path, mode, dev));
SYS_STUB(15, int, chmod, (const char * path, mode_t mode), (path, mode));
SYS_STUB(16, int, chown, (const char * path, int uid, int gid), (path, uid, gid));
SYS_STUB(20, pid_t, getpid, (void), ());
SYS_STUB(21, int, mount, (const char * type, const char * path, int flags, void * data), (type, path, flags, data));
SYS_STUB(22, int, unmount, (const char * path, int flags), (path, flags));
SYS_STUB(23, int, setuid, (uid_t uid), (uid));
SYS_STUB(24, uid_t, getuid, (void), ());
SYS_STUB(25, uid_t, geteuid, (void), ());
SYS_STUB(26, int, ptrace, (int req, pid_t pid, vaddr_t addr, int data), (req, pid, addr, data));
SYS_STUB(27, ssize_t, recvmsg, (int s, struct msghdr* msg, int flags), (s, msg, flags));
SYS_STUB(28, ssize_t, sendmsg, (int s, const struct msghdr* msg, int flags), (s, msg, flags));
SYS_STUB(29, ssize_t, recvfrom, (int s, void * buf, size_t len, int flags, struct sockaddr *__restrict from, socklen_t *__restrict fromlenaddr), (s, buf, len, flags, from, fromlenaddr));
SYS_STUB(30, int, accept, (int s, struct sockaddr *__restrict name, socklen_t * anamelen), (s, name, anamelen));
SYS_STUB(31, int, getpeername, (int fdes, struct sockaddr *__restrict asa, socklen_t * alen), (fdes, asa, alen));
SYS_STUB(32, int, getsockname, (int fdes, struct sockaddr *__restrict asa, socklen_t * alen), (fdes, asa, alen));
SYS_STUB(33, int, access, (const char * path, int amode), (path, amode));
SYS_STUB(34, int, chflags, (const char * path, u_long flags), (path, flags));
SYS_STUB(35, int, fchflags, (int fd, u_long flags), (fd, flags));
SYS_STUB(36, int, sync, (void), ());
SYS_STUB(37, int, kill, (int pid, int signum), (pid, signum));
SYS_STUB(39, pid_t, getppid, (void), ());
SYS_STUB(41, int, dup, (u_int fd), (fd));
SYS_STUB(42, int, pipe, (void), ());
SYS_STUB(43, gid_t, getegid, (void), ());
SYS_STUB(44, int, profil, (void * samples, size_t size, size_t offset, u_int scale), (samples, size, offset, scale));
SYS_STUB(45, int, ktrace, (const char * fname, int ops, int facs, int pid), (fname, ops, facs, pid));
SYS_STUB(47, gid_t, getgid, (void), ());
SYS_STUB(49, int, getlogin, (char * namebuf, u_int namelen), (namebuf, namelen));
SYS_STUB(50, int, setlogin, (const char * namebuf), (namebuf));
SYS_STUB(51, int, acct, (const char * path), (path));
SYS_STUB(53, int, sigaltstack, (const cheriabi_stack_t * ss, cheriabi_stack_t * oss), (ss, oss));
SYS_STUB_VA(54, int, ioctl, (int fd, u_long com, ...), (int fd, u_long com, va_list ap), (fd, com, ap), com);
SYS_STUB(55, int, reboot, (int opt), (opt));
SYS_STUB(56, int, revoke, (const char * path), (path));
SYS_STUB(57, int, symlink, (const char * path, const char * link), (path, link));
SYS_STUB(58, ssize_t, readlink, (const char * path, char * buf, size_t count), (path, buf, count));
SYS_STUB(59, int, execve, (const char * fname, struct chericap * argv, struct chericap * envv), (fname, argv, envv));
SYS_STUB(60, mode_t, umask, (mode_t newmask), (newmask));
SYS_STUB(61, int, chroot, (const char * path), (path));
SYS_STUB(65, int, msync, (void * addr, size_t len, int flags), (addr, len, flags));
SYS_STUB(66, int, vfork, (void), ());
SYS_STUB(73, int, munmap, (void * addr, size_t len), (addr, len));
SYS_STUB(74, int, mprotect, (const void * addr, size_t len, int prot), (addr, len, prot));
SYS_STUB(75, int, madvise, (void * addr, size_t len, int behav), (addr, len, behav));
SYS_STUB(78, int, mincore, (const void * addr, size_t len, char * vec), (addr, len, vec));
SYS_STUB(79, int, getgroups, (u_int gidsetsize, gid_t * gidset), (gidsetsize, gidset));
SYS_STUB(80, int, setgroups, (u_int gidsetsize, gid_t * gidset), (gidsetsize, gidset));
SYS_STUB(81, int, getpgrp, (void), ());
SYS_STUB(82, int, setpgid, (int pid, int pgid), (pid, pgid));
SYS_STUB(83, int, setitimer, (int which, const struct itimerval * itv, struct itimerval * oitv), (which, itv, oitv));
SYS_STUB(85, int, swapon, (const char * name), (name));
SYS_STUB(86, int, getitimer, (int which, struct itimerval * itv), (which, itv));
SYS_STUB(89, int, getdtablesize, (void), ());
SYS_STUB(90, int, dup2, (u_int from, u_int to), (from, to));
SYS_STUB_VA(92, int, fcntl, (int fd, int cmd, ...), (int fd, int cmd, va_list ap), (fd, cmd, ap), cmd);
SYS_STUB(93, int, select, (int nd, fd_set * in, fd_set * ou, fd_set * ex, struct timeval * tv), (nd, in, ou, ex, tv));
SYS_STUB(95, int, fsync, (int fd), (fd));
SYS_STUB(96, int, setpriority, (int which, int who, int prio), (which, who, prio));
SYS_STUB(97, int, socket, (int domain, int type, int protocol), (domain, type, protocol));
SYS_STUB(98, int, connect, (int s, const struct sockaddr * name, socklen_t namelen), (s, name, namelen));
SYS_STUB(100, int, getpriority, (int which, int who), (which, who));
SYS_STUB(104, int, bind, (int s, const struct sockaddr * name, socklen_t namelen), (s, name, namelen));
SYS_STUB(105, int, setsockopt, (int s, int level, int name, const void * val, socklen_t valsize), (s, level, name, val, valsize));
SYS_STUB(106, int, listen, (int s, int backlog), (s, backlog));
SYS_STUB(116, int, gettimeofday, (struct timeval * tp, struct timezone * tzp), (tp, tzp));
SYS_STUB(117, int, getrusage, (int who, struct rusage * rusage), (who, rusage));
SYS_STUB(118, int, getsockopt, (int s, int level, int name, void * val, socklen_t * avalsize), (s, level, name, val, avalsize));
SYS_STUB(120, int, readv, (int fd, struct iovec* iovp, u_int iovcnt), (fd, iovp, iovcnt));
SYS_STUB(121, int, writev, (int fd, struct iovec* iovp, u_int iovcnt), (fd, iovp, iovcnt));
SYS_STUB(122, int, settimeofday, (const struct timeval * tv, const struct timezone * tzp), (tv, tzp));
SYS_STUB(123, int, fchown, (int fd, int uid, int gid), (fd, uid, gid));
SYS_STUB(124, int, fchmod, (int fd, mode_t mode), (fd, mode));
SYS_STUB(126, int, setreuid, (int ruid, int euid), (ruid, euid));
SYS_STUB(127, int, setregid, (int rgid, int egid), (rgid, egid));
SYS_STUB(128, int, rename, (const char * from, const char * to), (from, to));
SYS_STUB(131, int, flock, (int fd, int how), (fd, how));
SYS_STUB(132, int, mkfifo, (const char * path, mode_t mode), (path, mode));
SYS_STUB(133, ssize_t, sendto, (int s, const void * buf, size_t len, int flags, const struct sockaddr * to, socklen_t tolen), (s, buf, len, flags, to, tolen));
SYS_STUB(134, int, shutdown, (int s, int how), (s, how));
SYS_STUB(135, int, socketpair, (int domain, int type, int protocol, int * rsv), (domain, type, protocol, rsv));
SYS_STUB(136, int, mkdir, (const char * path, mode_t mode), (path, mode));
SYS_STUB(137, int, rmdir, (const char * path), (path));
SYS_STUB(138, int, utimes, (const char * path, const struct timeval * tptr), (path, tptr));
SYS_STUB(140, int, adjtime, (const struct timeval * delta, struct timeval * olddelta), (delta, olddelta));
SYS_STUB(147, int, setsid, (void), ());
SYS_STUB(148, int, quotactl, (const char * path, int cmd, int uid, void * arg), (path, cmd, uid, arg));
SYS_STUB(154, int, nlm_syscall, (int debug_level, int grace_period, int addr_count, struct chericap * addrs), (debug_level, grace_period, addr_count, addrs));
SYS_STUB(155, int, nfssvc, (int flag, caddr_t argp), (flag, argp));
SYS_STUB(160, int, lgetfh, (const char * fname, struct fhandle * fhp), (fname, fhp));
SYS_STUB(161, int, getfh, (const char * fname, struct fhandle * fhp), (fname, fhp));
SYS_STUB(165, int, sysarch, (int op, char * parms), (op, parms));
SYS_STUB(166, int, rtprio, (int function, pid_t pid, struct rtprio * rtp), (function, pid, rtp));
SYS_STUB(175, int, setfib, (int fibnum), (fibnum));
SYS_STUB(176, int, ntp_adjtime, (struct timex * tp), (tp));
SYS_STUB(181, int, setgid, (gid_t gid), (gid));
SYS_STUB(182, int, setegid, (gid_t egid), (egid));
SYS_STUB(183, int, seteuid, (uid_t euid), (euid));
SYS_STUB(188, int, stat, (const char * path, struct stat * ub), (path, ub));
SYS_STUB(189, int, fstat, (int fd, struct stat * sb), (fd, sb));
SYS_STUB(190, int, lstat, (const char * path, struct stat * ub), (path, ub));
SYS_STUB(191, int, pathconf, (const char * path, int name), (path, name));
SYS_STUB(192, int, fpathconf, (int fd, int name), (fd, name));
SYS_STUB(194, int, getrlimit, (u_int which, struct rlimit * rlp), (which, rlp));
SYS_STUB(195, int, setrlimit, (u_int which, struct rlimit * rlp), (which, rlp));
SYS_STUB(196, int, getdirentries, (int fd, char * buf, u_int count, long * basep), (fd, buf, count, basep));
SYS_STUB(202, int, __sysctl, (int * name, u_int namelen, void * old, size_t * oldlenp, void * new, size_t newlen), (name, namelen, old, oldlenp, new, newlen));
SYS_STUB(203, int, mlock, (const void * addr, size_t len), (addr, len));
SYS_STUB(204, int, munlock, (const void * addr, size_t len), (addr, len));
SYS_STUB(205, int, undelete, (const char * path), (path));
SYS_STUB(206, int, futimes, (int fd, const struct timeval * tptr), (fd, tptr));
SYS_STUB(207, int, getpgid, (pid_t pid), (pid));
SYS_STUB(209, int, poll, (struct pollfd * fds, u_int nfds, int timeout), (fds, nfds, timeout));
SYS_STUB(221, int, semget, (key_t key, int nsems, int semflg), (key, nsems, semflg));
SYS_STUB(222, int, semop, (int semid, struct sembuf * sops, u_int nsops), (semid, sops, nsops));
SYS_STUB(225, int, msgget, (key_t key, int msgflg), (key, msgflg));
SYS_STUB(226, int, msgsnd, (int msqid, void * msgp, size_t msgsz, int msgflg), (msqid, msgp, msgsz, msgflg));
SYS_STUB(227, int, msgrcv, (int msqid, void * msgp, size_t msgsz, long msgtyp, int msgflg), (msqid, msgp, msgsz, msgtyp, msgflg));
SYS_STUB(228, void*, shmat, (int shmid, void * shmaddr, int shmflg), (shmid, shmaddr, shmflg));
SYS_STUB(230, int, shmdt, (void * shmaddr), (shmaddr));
SYS_STUB(231, int, shmget, (key_t key, int size, int shmflg), (key, size, shmflg));
SYS_STUB(232, int, clock_gettime, (clockid_t clock_id, struct timespec * tp), (clock_id, tp));
SYS_STUB(233, int, clock_settime, (clockid_t clock_id, const struct timespec * tp), (clock_id, tp));
SYS_STUB(234, int, clock_getres, (clockid_t clock_id, struct timespec * tp), (clock_id, tp));
SYS_STUB(235, int, ktimer_create, (clockid_t clock_id, struct sigevent* evp, int * timerid), (clock_id, evp, timerid));
SYS_STUB(236, int, ktimer_delete, (int timerid), (timerid));
SYS_STUB(237, int, ktimer_settime, (int timerid, int flags, const struct itimerspec * value, struct itimerspec * ovalue), (timerid, flags, value, ovalue));
SYS_STUB(238, int, ktimer_gettime, (int timerid, struct itimerspec * value), (timerid, value));
SYS_STUB(239, int, ktimer_getoverrun, (int timerid), (timerid));
SYS_STUB(240, int, nanosleep, (const struct timespec * rqtp, struct timespec * rmtp), (rqtp, rmtp));
SYS_STUB(241, int, ffclock_getcounter, (ffcounter * ffcount), (ffcount));
SYS_STUB(242, int, ffclock_setestimate, (struct ffclock_estimate * cest), (cest));
SYS_STUB(243, int, ffclock_getestimate, (struct ffclock_estimate * cest), (cest));
SYS_STUB(247, int, clock_getcpuclockid2, (id_t id, int which, clockid_t * clock_id), (id, which, clock_id));
SYS_STUB(248, int, ntp_gettime, (struct ntptimeval * ntvp), (ntvp));
SYS_STUB(250, int, minherit, (void * addr, size_t len, int inherit), (addr, len, inherit));
SYS_STUB(251, int, rfork, (int flags), (flags));
SYS_STUB(253, int, issetugid, (void), ());
SYS_STUB(254, int, lchown, (const char * path, int uid, int gid), (path, uid, gid));
SYS_STUB(255, int, aio_read, (struct aiocb* aiocbp), (aiocbp));
SYS_STUB(256, int, aio_write, (struct aiocb* aiocbp), (aiocbp));
SYS_STUB(257, int, lio_listio, (int mode, struct aiocb*const * acb_list, int nent, struct sigevent* sig), (mode, acb_list, nent, sig));
SYS_STUB(272, int, getdents, (int fd, char * buf, size_t count), (fd, buf, count));
SYS_STUB(274, int, lchmod, (const char * path, mode_t mode), (path, mode));
SYS_STUB(276, int, lutimes, (const char * path, const struct timeval * tptr), (path, tptr));
SYS_STUB(278, int, nstat, (const char * path, struct nstat * ub), (path, ub));
SYS_STUB(279, int, nfstat, (int fd, struct nstat * sb), (fd, sb));
SYS_STUB(280, int, nlstat, (const char * path, struct nstat * ub), (path, ub));
SYS_STUB(289, ssize_t, preadv, (int fd, struct iovec* iovp, u_int iovcnt, off_t offset), (fd, iovp, iovcnt, offset));
SYS_STUB(290, ssize_t, pwritev, (int fd, struct iovec* iovp, u_int iovcnt, off_t offset), (fd, iovp, iovcnt, offset));
SYS_STUB(298, int, fhopen, (const struct fhandle * u_fhp, int flags), (u_fhp, flags));
SYS_STUB(299, int, fhstat, (const struct fhandle * u_fhp, struct stat * sb), (u_fhp, sb));
SYS_STUB(300, int, modnext, (int modid), (modid));
SYS_STUB(301, int, modstat, (int modid, struct module_stat * stat), (modid, stat));
SYS_STUB(302, int, modfnext, (int modid), (modid));
SYS_STUB(303, int, modfind, (const char * name), (name));
SYS_STUB(304, int, kldload, (const char * file), (file));
SYS_STUB(305, int, kldunload, (int fileid), (fileid));
SYS_STUB(306, int, kldfind, (const char * file), (file));
SYS_STUB(307, int, kldnext, (int fileid), (fileid));
SYS_STUB(308, int, kldstat, (int fileid, struct kld_file_stat * stat), (fileid, stat));
SYS_STUB(309, int, kldfirstmod, (int fileid), (fileid));
SYS_STUB(310, int, getsid, (pid_t pid), (pid));
SYS_STUB(311, int, setresuid, (uid_t ruid, uid_t euid, uid_t suid), (ruid, euid, suid));
SYS_STUB(312, int, setresgid, (gid_t rgid, gid_t egid, gid_t sgid), (rgid, egid, sgid));
SYS_STUB(314, int, aio_return, (struct aiocb* aiocbp), (aiocbp));
SYS_STUB(315, int, aio_suspend, (struct aiocb*const * aiocbp, int nent, const struct timespec * timeout), (aiocbp, nent, timeout));
SYS_STUB(316, int, aio_cancel, (int fd, struct aiocb* aiocbp), (fd, aiocbp));
SYS_STUB(317, int, aio_error, (struct aiocb* aiocbp), (aiocbp));
SYS_STUB(324, int, mlockall, (int how), (how));
SYS_STUB(325, int, munlockall, (void), ());
SYS_STUB(326, int, __getcwd, (char * buf, u_int buflen), (buf, buflen));
SYS_STUB(327, int, sched_setparam, (pid_t pid, const struct sched_param * param), (pid, param));
SYS_STUB(328, int, sched_getparam, (pid_t pid, struct sched_param * param), (pid, param));
SYS_STUB(329, int, sched_setscheduler, (pid_t pid, int policy, const struct sched_param * param), (pid, policy, param));
SYS_STUB(330, int, sched_getscheduler, (pid_t pid), (pid));
SYS_STUB(331, int, sched_yield, (void), ());
SYS_STUB(332, int, sched_get_priority_max, (int policy), (policy));
SYS_STUB(333, int, sched_get_priority_min, (int policy), (policy));
SYS_STUB(334, int, sched_rr_get_interval, (pid_t pid, struct timespec * interval), (pid, interval));
SYS_STUB(335, int, utrace, (const void * addr, size_t len), (addr, len));
SYS_STUB(337, int, kldsym, (int fileid, int cmd, struct kld_sym_lookup* data), (fileid, cmd, data));
SYS_STUB(338, int, jail, (struct jail* jailp), (jailp));
SYS_STUB(340, int, sigprocmask, (int how, const sigset_t * set, sigset_t * oset), (how, set, oset));
SYS_STUB(341, int, sigsuspend, (const sigset_t * sigmask), (sigmask));
SYS_STUB(343, int, sigpending, (sigset_t * set), (set));
SYS_STUB(345, int, sigtimedwait, (const sigset_t * set, struct siginfo* info, const struct timespec * timeout), (set, info, timeout));
SYS_STUB(346, int, sigwaitinfo, (const sigset_t * set, struct siginfo* info), (set, info));
SYS_STUB(347, int, __acl_get_file, (const char * path, acl_type_t type, struct acl * aclp), (path, type, aclp));
SYS_STUB(348, int, __acl_set_file, (const char * path, acl_type_t type, struct acl * aclp), (path, type, aclp));
SYS_STUB(349, int, __acl_get_fd, (int filedes, acl_type_t type, struct acl * aclp), (filedes, type, aclp));
SYS_STUB(350, int, __acl_set_fd, (int filedes, acl_type_t type, struct acl * aclp), (filedes, type, aclp));
SYS_STUB(351, int, __acl_delete_file, (const char * path, acl_type_t type), (path, type));
SYS_STUB(352, int, __acl_delete_fd, (int filedes, acl_type_t type), (filedes, type));
SYS_STUB(353, int, __acl_aclcheck_file, (const char * path, acl_type_t type, struct acl * aclp), (path, type, aclp));
SYS_STUB(354, int, __acl_aclcheck_fd, (int filedes, acl_type_t type, struct acl * aclp), (filedes, type, aclp));
SYS_STUB(355, int, extattrctl, (const char * path, int cmd, const char * filename, int attrnamespace, const char * attrname), (path, cmd, filename, attrnamespace, attrname));
SYS_STUB(356, ssize_t, extattr_set_file, (const char * path, int attrnamespace, const char * attrname, void * data, size_t nbytes), (path, attrnamespace, attrname, data, nbytes));
SYS_STUB(357, ssize_t, extattr_get_file, (const char * path, int attrnamespace, const char * attrname, void * data, size_t nbytes), (path, attrnamespace, attrname, data, nbytes));
SYS_STUB(358, int, extattr_delete_file, (const char * path, int attrnamespace, const char * attrname), (path, attrnamespace, attrname));
SYS_STUB(359, int, aio_waitcomplete, (struct aiocb** aiocbp, struct timespec * timeout), (aiocbp, timeout));
SYS_STUB(360, int, getresuid, (uid_t * ruid, uid_t * euid, uid_t * suid), (ruid, euid, suid));
SYS_STUB(361, int, getresgid, (gid_t * rgid, gid_t * egid, gid_t * sgid), (rgid, egid, sgid));
SYS_STUB(362, int, kqueue, (void), ());
SYS_STUB(363, int, kevent, (int fd, const struct kevent* changelist, int nchanges, struct kevent* eventlist, int nevents, const struct timespec * timeout), (fd, changelist, nchanges, eventlist, nevents, timeout));
SYS_STUB(371, ssize_t, extattr_set_fd, (int fd, int attrnamespace, const char * attrname, void * data, size_t nbytes), (fd, attrnamespace, attrname, data, nbytes));
SYS_STUB(372, ssize_t, extattr_get_fd, (int fd, int attrnamespace, const char * attrname, void * data, size_t nbytes), (fd, attrnamespace, attrname, data, nbytes));
SYS_STUB(373, int, extattr_delete_fd, (int fd, int attrnamespace, const char * attrname), (fd, attrnamespace, attrname));
SYS_STUB(374, int, __setugid, (int flag), (flag));
SYS_STUB(376, int, eaccess, (char * path, int amode), (path, amode));
SYS_STUB(378, int, nmount, (struct iovec* iovp, unsigned int iovcnt, int flags), (iovp, iovcnt, flags));
SYS_STUB(384, int, __mac_get_proc, (struct mac* mac_p), (mac_p));
SYS_STUB(385, int, __mac_set_proc, (struct mac* mac_p), (mac_p));
SYS_STUB(386, int, __mac_get_fd, (int fd, struct mac* mac_p), (fd, mac_p));
SYS_STUB(387, int, __mac_get_file, (const char * path_p, struct mac* mac_p), (path_p, mac_p));
SYS_STUB(388, int, __mac_set_fd, (int fd, struct mac* mac_p), (fd, mac_p));
SYS_STUB(389, int, __mac_set_file, (const char * path_p, struct mac* mac_p), (path_p, mac_p));
SYS_STUB(390, int, kenv, (int what, const char * name, char * value, int len), (what, name, value, len));
SYS_STUB(391, int, lchflags, (const char * path, u_long flags), (path, flags));
SYS_STUB(392, int, uuidgen, (struct uuid * store, int count), (store, count));
SYS_STUB(393, int, sendfile, (int fd, int s, off_t offset, size_t nbytes, struct sf_hdtr* hdtr, off_t * sbytes, int flags), (fd, s, offset, nbytes, hdtr, sbytes, flags));
SYS_STUB(394, int, mac_syscall, (const char * policy, int call, void * arg), (policy, call, arg));
SYS_STUB(395, int, getfsstat, (struct statfs * buf, long bufsize, int flags), (buf, bufsize, flags));
SYS_STUB(396, int, statfs, (char * path, struct statfs * buf), (path, buf));
SYS_STUB(397, int, fstatfs, (int fd, struct statfs * buf), (fd, buf));
SYS_STUB(398, int, fhstatfs, (const struct fhandle * u_fhp, struct statfs * buf), (u_fhp, buf));
SYS_STUB(409, int, __mac_get_pid, (pid_t pid, struct mac* mac_p), (pid, mac_p));
SYS_STUB(410, int, __mac_get_link, (const char * path_p, struct mac* mac_p), (path_p, mac_p));
SYS_STUB(411, int, __mac_set_link, (const char * path_p, struct mac* mac_p), (path_p, mac_p));
SYS_STUB(412, ssize_t, extattr_set_link, (const char * path, int attrnamespace, const char * attrname, void * data, size_t nbytes), (path, attrnamespace, attrname, data, nbytes));
SYS_STUB(413, ssize_t, extattr_get_link, (const char * path, int attrnamespace, const char * attrname, void * data, size_t nbytes), (path, attrnamespace, attrname, data, nbytes));
SYS_STUB(414, int, extattr_delete_link, (const char * path, int attrnamespace, const char * attrname), (path, attrnamespace, attrname));
SYS_STUB(415, int, __mac_execve, (char * fname, struct chericap * argv, struct chericap * envv, struct mac* mac_p), (fname, argv, envv, mac_p));
SYS_STUB(416, int, sigaction, (int sig, struct sigaction* act, struct sigaction* oact), (sig, act, oact));
SYS_STUB(417, int, sigreturn, (const ucontext_t* sigcntxp), (sigcntxp));
SYS_STUB(421, int, getcontext, (ucontext_t* ucp), (ucp));
SYS_STUB(422, int, setcontext, (const ucontext_t* ucp), (ucp));
SYS_STUB(423, int, swapcontext, (ucontext_t* oucp, const ucontext_t* ucp), (oucp, ucp));
SYS_STUB(424, int, swapoff, (const char * name), (name));
SYS_STUB(425, int, __acl_get_link, (const char * path, acl_type_t type, struct acl * aclp), (path, type, aclp));
SYS_STUB(426, int, __acl_set_link, (const char * path, acl_type_t type, struct acl * aclp), (path, type, aclp));
SYS_STUB(427, int, __acl_delete_link, (const char * path, acl_type_t type), (path, type));
SYS_STUB(428, int, __acl_aclcheck_link, (const char * path, acl_type_t type, struct acl * aclp), (path, type, aclp));
SYS_STUB(429, int, sigwait, (const sigset_t * set, int * sig), (set, sig));
SYS_STUB(430, int, thr_create, (ucontext_t* ctx, long * id, int flags), (ctx, id, flags));
SYS_STUB(431, void, thr_exit, (long * state), (state));
SYS_STUB(432, int, thr_self, (long * id), (id));
SYS_STUB(433, int, thr_kill, (long id, int sig), (id, sig));
SYS_STUB(436, int, jail_attach, (int jid), (jid));
SYS_STUB(437, ssize_t, extattr_list_fd, (int fd, int attrnamespace, void * data, size_t nbytes), (fd, attrnamespace, data, nbytes));
SYS_STUB(438, ssize_t, extattr_list_file, (const char * path, int attrnamespace, void * data, size_t nbytes), (path, attrnamespace, data, nbytes));
SYS_STUB(439, ssize_t, extattr_list_link, (const char * path, int attrnamespace, void * data, size_t nbytes), (path, attrnamespace, data, nbytes));
SYS_STUB(441, int, ksem_timedwait, (semid_t id, const struct timespec * abstime), (id, abstime));
SYS_STUB(442, int, thr_suspend, (const struct timespec * timeout), (timeout));
SYS_STUB(443, int, thr_wake, (long id), (id));
SYS_STUB(444, int, kldunloadf, (int fileid, int flags), (fileid, flags));
SYS_STUB(445, int, audit, (const void * record, u_int length), (record, length));
SYS_STUB(446, int, auditon, (int cmd, void * data, u_int length), (cmd, data, length));
SYS_STUB(447, int, getauid, (uid_t * auid), (auid));
SYS_STUB(448, int, setauid, (uid_t * auid), (auid));
SYS_STUB(449, int, getaudit, (struct auditinfo * auditinfo), (auditinfo));
SYS_STUB(450, int, setaudit, (struct auditinfo * auditinfo), (auditinfo));
SYS_STUB(451, int, getaudit_addr, (struct auditinfo_addr * auditinfo_addr, u_int length), (auditinfo_addr, length));
SYS_STUB(452, int, setaudit_addr, (struct auditinfo_addr * auditinfo_addr, u_int length), (auditinfo_addr, length));
SYS_STUB(453, int, auditctl, (const char * path), (path));
SYS_STUB(454, int, _umtx_op, (void * obj, int op, u_long val, void * uaddr1, void * uaddr2), (obj, op, val, uaddr1, uaddr2));
SYS_STUB(455, int, thr_new, (struct thr_param* param, int param_size), (param, param_size));
SYS_STUB(456, int, sigqueue, (pid_t pid, int signum, void * value), (pid, signum, value));
SYS_STUB(457, int, kmq_open, (const char * path, int flags, mode_t mode, const struct mq_attr * attr), (path, flags, mode, attr));
SYS_STUB(458, int, kmq_setattr, (int mqd, const struct mq_attr * attr, struct mq_attr * oattr), (mqd, attr, oattr));
SYS_STUB(459, int, kmq_timedreceive, (int mqd, char * msg_ptr, size_t msg_len, unsigned * msg_prio, const struct timespec * abs_timeout), (mqd, msg_ptr, msg_len, msg_prio, abs_timeout));
SYS_STUB(460, int, kmq_timedsend, (int mqd, const char * msg_ptr, size_t msg_len, unsigned msg_prio, const struct timespec * abs_timeout), (mqd, msg_ptr, msg_len, msg_prio, abs_timeout));
SYS_STUB(461, int, kmq_notify, (int mqd, const struct sigevent* sigev), (mqd, sigev));
SYS_STUB(462, int, kmq_unlink, (const char * path), (path));
SYS_STUB(464, int, thr_set_name, (long id, const char * name), (id, name));
SYS_STUB(465, int, aio_fsync, (int op, struct aiocb* aiocbp), (op, aiocbp));
SYS_STUB(466, int, rtprio_thread, (int function, lwpid_t lwpid, struct rtprio * rtp), (function, lwpid, rtp));
SYS_STUB(471, int, sctp_peeloff, (int sd, uint32_t name), (sd, name));
SYS_STUB(475, ssize_t, pread, (int fd, void * buf, size_t nbyte, off_t offset), (fd, buf, nbyte, offset));
SYS_STUB(476, ssize_t, pwrite, (int fd, const void * buf, size_t nbyte, off_t offset), (fd, buf, nbyte, offset));
SYS_STUB(477, void*, mmap, (void * addr, size_t len, int prot, int flags, int fd, off_t pos), (addr, len, prot, flags, fd, pos));
SYS_STUB(478, off_t, lseek, (int fd, off_t offset, int whence), (fd, offset, whence));
SYS_STUB(479, int, truncate, (const char * path, off_t length), (path, length));
SYS_STUB(480, int, ftruncate, (int fd, off_t length), (fd, length));
SYS_STUB(481, int, thr_kill2, (pid_t pid, long id, int sig), (pid, id, sig));
SYS_STUB(482, int, shm_open, (const char * path, int flags, mode_t mode), (path, flags, mode));
SYS_STUB(483, int, shm_unlink, (const char * path), (path));
SYS_STUB(484, int, cpuset, (cpusetid_t * setid), (setid));
SYS_STUB(485, int, cpuset_setid, (cpuwhich_t which, id_t id, cpusetid_t setid), (which, id, setid));
SYS_STUB(486, int, cpuset_getid, (cpulevel_t level, cpuwhich_t which, id_t id, cpusetid_t * setid), (level, which, id, setid));
SYS_STUB(487, int, cpuset_getaffinity, (cpulevel_t level, cpuwhich_t which, id_t id, size_t cpusetsize, cpuset_t * mask), (level, which, id, cpusetsize, mask));
SYS_STUB(488, int, cpuset_setaffinity, (cpulevel_t level, cpuwhich_t which, id_t id, size_t cpusetsize, const cpuset_t * mask), (level, which, id, cpusetsize, mask));
SYS_STUB(489, int, faccessat, (int fd, const char * path, int amode, int flag), (fd, path, amode, flag));
SYS_STUB(490, int, fchmodat, (int fd, const char * path, mode_t mode, int flag), (fd, path, mode, flag));
SYS_STUB(491, int, fchownat, (int fd, const char * path, uid_t uid, gid_t gid, int flag), (fd, path, uid, gid, flag));
SYS_STUB(492, int, fexecve, (int fd, struct chericap * argv, struct chericap * envv), (fd, argv, envv));
SYS_STUB(493, int, fstatat, (int fd, const char * path, struct stat * buf, int flag), (fd, path, buf, flag));
SYS_STUB(494, int, futimesat, (int fd, const char * path, const struct timeval * times), (fd, path, times));
SYS_STUB(495, int, linkat, (int fd1, const char * path1, int fd2, const char * path2, int flag), (fd1, path1, fd2, path2, flag));
SYS_STUB(496, int, mkdirat, (int fd, const char * path, mode_t mode), (fd, path, mode));
SYS_STUB(497, int, mkfifoat, (int fd, const char * path, mode_t mode), (fd, path, mode));
SYS_STUB(498, int, mknodat, (int fd, const char * path, mode_t mode, dev_t dev), (fd, path, mode, dev));
SYS_STUB(499, int, openat, (int fd, const char * path, int flag, mode_t mode), (fd, path, flag, mode));
SYS_STUB(500, int, readlinkat, (int fd, const char * path, char * buf, size_t bufsize), (fd, path, buf, bufsize));
SYS_STUB(501, int, renameat, (int oldfd, const char * old, int newfd, const char * new), (oldfd, old, newfd, new));
SYS_STUB(502, int, symlinkat, (const char * path1, int fd, const char * path2), (path1, fd, path2));
SYS_STUB(503, int, unlinkat, (int fd, const char * path, int flag), (fd, path, flag));
SYS_STUB(504, int, posix_openpt, (int flags), (flags));
SYS_STUB(505, int, gssd_syscall, (const char * path), (path));
SYS_STUB(506, int, jail_get, (struct iovec* iovp, unsigned int iovcnt, int flags), (iovp, iovcnt, flags));
SYS_STUB(507, int, jail_set, (struct iovec* iovp, unsigned int iovcnt, int flags), (iovp, iovcnt, flags));
SYS_STUB(508, int, jail_remove, (int jid), (jid));
SYS_STUB(509, int, closefrom, (int lowfd), (lowfd));
SYS_STUB(510, int, __semctl, (int semid, int semnum, int cmd, union semun* arg), (semid, semnum, cmd, arg));
SYS_STUB(511, int, msgctl, (int msqid, int cmd, struct msqid_ds* buf), (msqid, cmd, buf));
SYS_STUB(512, int, shmctl, (int shmid, int cmd, struct shmid_ds * buf), (shmid, cmd, buf));
SYS_STUB(513, int, lpathconf, (const char * path, int name), (path, name));
SYS_STUB(515, int, __cap_rights_get, (int version, int fd, cap_rights_t * rightsp), (version, fd, rightsp));
SYS_STUB(516, int, cap_enter, (void), ());
SYS_STUB(517, int, cap_getmode, (u_int * modep), (modep));
SYS_STUB(518, int, pdfork, (int * fdp, int flags), (fdp, flags));
SYS_STUB(519, int, pdkill, (int fd, int signum), (fd, signum));
SYS_STUB(520, int, pdgetpid, (int fd, pid_t * pidp), (fd, pidp));
SYS_STUB(522, int, pselect, (int nd, fd_set * in, fd_set * ou, fd_set * ex, const struct timespec * ts, const sigset_t * sm), (nd, in, ou, ex, ts, sm));
SYS_STUB(523, int, getloginclass, (char * namebuf, size_t namelen), (namebuf, namelen));
SYS_STUB(524, int, setloginclass, (const char * namebuf), (namebuf));
SYS_STUB(525, int, rctl_get_racct, (const void * inbufp, size_t inbuflen, void * outbufp, size_t outbuflen), (inbufp, inbuflen, outbufp, outbuflen));
SYS_STUB(526, int, rctl_get_rules, (const void * inbufp, size_t inbuflen, void * outbufp, size_t outbuflen), (inbufp, inbuflen, outbufp, outbuflen));
SYS_STUB(527, int, rctl_get_limits, (const void * inbufp, size_t inbuflen, void * outbufp, size_t outbuflen), (inbufp, inbuflen, outbufp, outbuflen));
SYS_STUB(528, int, rctl_add_rule, (const void * inbufp, size_t inbuflen, void * outbufp, size_t outbuflen), (inbufp, inbuflen, outbufp, outbuflen));
SYS_STUB(529, int, rctl_remove_rule, (const void * inbufp, size_t inbuflen, void * outbufp, size_t outbuflen), (inbufp, inbuflen, outbufp, outbuflen));
SYS_STUB(530, int, posix_fallocate, (int fd, off_t offset, off_t len), (fd, offset, len));
SYS_STUB(531, int, posix_fadvise, (int fd, off_t offset, off_t len, int advice), (fd, offset, len, advice));
SYS_STUB(532, int, wait6, (int idtype, id_t id, int * status, int options, struct __wrusage * wrusage, struct siginfo* info), (idtype, id, status, options, wrusage, info));
SYS_STUB(533, int, cap_rights_limit, (int fd, cap_rights_t * rightsp), (fd, rightsp));
SYS_STUB(534, int, cap_ioctls_limit, (int fd, const u_long * cmds, size_t ncmds), (fd, cmds, ncmds));
SYS_STUB(535, ssize_t, cap_ioctls_get, (int fd, u_long * cmds, size_t maxcmds), (fd, cmds, maxcmds));
SYS_STUB(536, int, cap_fcntls_limit, (int fd, uint32_t fcntlrights), (fd, fcntlrights));
SYS_STUB(537, int, cap_fcntls_get, (int fd, uint32_t * fcntlrightsp), (fd, fcntlrightsp));
SYS_STUB(538, int, bindat, (int fd, int s, const struct sockaddr * name, socklen_t namelen), (fd, s, name, namelen));
SYS_STUB(539, int, connectat, (int fd, int s, const struct sockaddr * name, socklen_t namelen), (fd, s, name, namelen));
SYS_STUB(540, int, chflagsat, (int fd, const char * path, u_long flags, int atflag), (fd, path, flags, atflag));
SYS_STUB(541, int, accept4, (int s, struct sockaddr *__restrict name, socklen_t *__restrict anamelen, int flags), (s, name, anamelen, flags));
SYS_STUB(542, int, pipe2, (int * fildes, int flags), (fildes, flags));
SYS_STUB(543, int, aio_mlock, (struct aiocb* aiocbp), (aiocbp));
SYS_STUB(544, int, procctl, (int idtype, id_t id, int com, void * data), (idtype, id, com, data));
SYS_STUB(545, int, ppoll, (struct pollfd * fds, u_int nfds, const struct timespec * ts, const sigset_t * set), (fds, nfds, ts, set));
SYS_STUB(546, int, futimens, (int fd, const struct timespec * times), (fd, times));
SYS_STUB(547, int, utimensat, (int fd, const char * path, const struct timespec * times, int flag), (fd, path, times, flag));
SYS_STUB(548, int, numa_getaffinity, (cpuwhich_t which, id_t id, struct vm_domain_policy_entry * policy), (which, id, policy));
SYS_STUB(549, int, numa_setaffinity, (cpuwhich_t which, id_t id, const struct vm_domain_policy_entry * policy), (which, id, policy));
