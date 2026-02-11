translate_files(char *pathes[], FILE *output[], da_build_t *builder)
{
#if defined HAVE_IO_H && !defined __CYGWIN__
    struct _finddata_t fileinfo;
    long handle;
#endif
    int num = 0;

    fputs("parsing dictionaries...\n", stderr);

    for (; *pathes != NULL; pathes++) {
#if defined HAVE_IO_H && !defined __CYGWIN__
	handle = _findfirst(*pathes, &fileinfo);
	if (handle < 0)
	    break;
	do {
	    if (translate(fileinfo.name, output, builder) < 0)
		return -1;
	    num++;
	} while (!_findnext(handle, &fileinfo));
	_findclose(handle);
#else
	if (translate(*pathes, output, builder) < 0)
	    return -1;
	num++;
#endif
    }

    return num;
}
