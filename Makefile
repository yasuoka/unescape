PROG=	unescape_test
SRCS=	unescape.c unescape_test.c
CFLAGS=	-O0 -g
NOMAN=	#

test: ${PROG}
	./${PROG}

.include <bsd.prog.mk>
