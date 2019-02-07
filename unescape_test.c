/*
 * Copyright (c) 2019 YASUOKA Masahiko <yasuoka@yasuoka.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *unescape(const char *, char *, size_t);

#define ASSERT(_cond)							\
	do {								\
		if (!(_cond)) {						\
			fprintf(stderr,					\
			    "ASSERT(%s) failed in %s():%s:%d",		\
			    #_cond, __func__, __FILE__, __LINE__);	\
			abort();					\
		}							\
	} while (0/*CONSTCOND*/)


static void
test(const char *in, const char *expect)
{
	const char *ret;
	char buf[128];

	ret = unescape(in, buf, sizeof(buf));
	ASSERT(ret != NULL);
	ASSERT(strcmp(ret, expect) == 0);
}

int
main(int argc, char *argv[])
{
	/* RFC 3629, 7. Examples */
	test("\\u0041\\u2262\\u0391\\u002E", "\x41\xE2\x89\xA2\xCE\x91\x2E");
	test("\\uD55C\\uAD6D\\uC5B4", "\xED\x95\x9C\xEA\xB5\xAD\xEC\x96\xB4");
	test("\\u65E5\\u672C\\u8A9E", "\xE6\x97\xA5\xE6\x9C\xAC\xE8\xAA\x9E");
	/* U+233B4 => 0xD84C 0xDFB4 */
	test("\\ud84c\\udfb4", "\xF0\xA3\x8E\xB4");

	/* no escape */
	test("hello world", "hello world");

	test("hello world\\n", "hello world\n");
	test("hello world\\r", "hello world\r");
	test("hello world\\u0000", "hello world");
	test("hello \\\"world\\\"", "hello \"world\"");
	test("hello\\\\world", "hello\\world");
	test("hello\\bworld", "hello\x08world");
	test("hello\\tworld", "hello\x09world");
	test("hello\\fworld", "hello\x0Cworld");

	exit(0);
}
