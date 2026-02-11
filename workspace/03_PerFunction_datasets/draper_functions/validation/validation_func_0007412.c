completepath(path, len, argc, argvp, exe)
CONST char *path;
int len, argc;
char ***argvp;
int exe;
{
# ifdef	DEP_DOSPATH
	char cwd[4];
# endif
# if	defined (DOUBLESLASH) || defined (DEP_URLPATH)
	int n;
# endif
	CONST char *dir, *file;
	int dlen;

	dlen = 0;
# ifdef	DEP_DOSPATH
	if (_dospath(path)) dlen = 2;
# endif
	dir = &(path[dlen]);

	if ((file = strrdelim(dir, 0))) {
		if (file == dir) {
			dlen++;
			file++;
		}
# ifdef	DOUBLESLASH
		else if ((n = isdslash(path)) && file < &(path[n])) {
			if (path[n - 1] != _SC_) return(argc);
			dlen = n;
			file = &(path[n]);
			if (*file == _SC_) file++;
		}
# endif
# ifdef	DEP_URLPATH
		else if ((n = _urlpath(path, NULL, NULL)) && file < &(path[n]))
			return(argc);
# endif
		else dlen += file++ - dir;
		return(completefile(file, strlen(file), argc, argvp,
			path, dlen, exe));
	}
# if	!defined (NOUID) && !defined (NOGETPWENT)
	else if (*path == '~')
		return(completeuser(&(path[1]), len - 1, argc, argvp, 1));
# endif
# ifdef	DEP_DOSPATH
	else if (dir != path) {
		len -= dlen;
		dlen = gendospath(cwd, *path, '.') - cwd;
		return(completefile(dir, len, argc, argvp, cwd, dlen, exe));
	}
# endif
	else if (exe) return(completeexe(path, len, argc, argvp));

	return(completefile(path, len, argc, argvp, curpath, 1, exe));
}
