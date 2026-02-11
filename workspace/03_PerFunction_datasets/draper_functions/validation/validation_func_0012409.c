safe_fopen(char const* filename, char const* mode)
{

    FILE* f = 0;
#ifdef _MSC_VER
    errno_t err = fopen_s(&f, filename, mode);
    if (err != 0)
    {
        char buf[94];
        strerror_s(buf, sizeof(buf), errno);
	fprintf(stderr, "%s: unable to open %s: %s\n",
		whoami, filename, buf);
	exit(2);
    }
#else
    f = fopen(filename, mode);
    if (f == NULL)
    {
	fprintf(stderr, "%s: unable to open %s: %s\n",
		whoami, filename, strerror(errno));
	exit(2);
    }
#endif
    return f;
}
