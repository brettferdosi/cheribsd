# $FreeBSD$

.include <src.opts.mk>

PACKAGE=	lib${LIB}
LIB=		compiler_rt
NO_PIC=
WARNS?=		2

CFLAGS+=	${PICFLAG}
CFLAGS+=	-fvisibility=hidden
CFLAGS+=	-DVISIBILITY_HIDDEN
CFLAGS+=	-I${SRCTOP}/contrib/subrepo-cheri-libcxxrt/src

# gcc has incompatible internal declarations for __divtc3 and __multc3, but has
# no option to silence its warning, so make warnings non-fatal.
MK_WERROR.gcc=	no

.include "Makefile.inc"

.if ${MK_INSTALLLIB} != "no"
SYMLINKS+=	libcompiler_rt.a ${LIBDIR}/libgcc.a
.endif
.if ${MK_PROFILE} != "no"
SYMLINKS+=	libcompiler_rt_p.a ${LIBDIR}/libgcc_p.a
.endif

.include <bsd.lib.mk>
