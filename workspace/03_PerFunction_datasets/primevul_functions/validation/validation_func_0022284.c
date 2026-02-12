changedir(char *path)
{
#if defined(MSDOS)


    if (isalpha((unsigned char)path[0]) && (path[1] == ':')) {
	int driveno = toupper((unsigned char)path[0]) - 'A';

# if defined(__EMX__) || defined(__WATCOMC__)
	(void) _chdrive(driveno + 1);
# elif defined(__DJGPP__)
	(void) setdisk(driveno);
# endif
	path += 2;
    }

    if (*path)
	if (chdir(path))
	    return 1;

    return 0;

#elif defined(_WIN32)
    LPWSTR pathw = UnicodeText(path, encoding);
    int ret = !SetCurrentDirectoryW(pathw);
    free(pathw);
    return ret;
#elif defined(__EMX__) && defined(OS2)
    return _chdir2(path);
#else
    return chdir(path);
#endif
}
