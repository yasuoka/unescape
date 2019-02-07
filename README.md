unescape.c
==========

Simple implementation which unescapes JSON's escaped strings.

Example:

    $ cat > example.c
    #include <stdio.h>
    const char *unescape(const char *, char *, size_t);
    main()
    {
        char buf[80];
        printf("%s\n",
            unescape("\\u3053\\u3093\\u306b\\u3061\\u306f\\u4e16\\u754c\\uff01",
            buf, sizeof(buf)));
    }
    ^D
    $
    $ cc -o example example.c unescape.c
    $
    $ ./example
    こんにちは世界！
    $

