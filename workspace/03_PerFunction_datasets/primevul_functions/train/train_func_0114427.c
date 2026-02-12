void mingw_startup(void)
{
	int i, maxlen, argc;
	char *buffer;
	wchar_t **wenv, **wargv;
	_startupinfo si;


	si.newmode = 0;
	if (__wgetmainargs(&argc, &wargv, &wenv, _CRT_glob, &si) < 0)
		die_startup();


	maxlen = wcslen(_wpgmptr);
	for (i = 1; i < argc; i++)
		maxlen = max(maxlen, wcslen(wargv[i]));
	for (i = 0; wenv[i]; i++)
		maxlen = max(maxlen, wcslen(wenv[i]));


	environ_size = i + 1;
	environ_alloc = alloc_nr(environ_size * sizeof(char*));
	environ = malloc_startup(environ_alloc);


	maxlen = 3 * maxlen + 1;
	buffer = malloc_startup(maxlen);


	__argv[0] = wcstoutfdup_startup(buffer, _wpgmptr, maxlen);
	for (i = 1; i < argc; i++)
		__argv[i] = wcstoutfdup_startup(buffer, wargv[i], maxlen);
	for (i = 0; wenv[i]; i++)
		environ[i] = wcstoutfdup_startup(buffer, wenv[i], maxlen);
	environ[i] = NULL;
	free(buffer);


	qsort(environ, i, sizeof(char*), compareenv);


	setup_windows_environment();


	InitializeCriticalSection(&pinfo_cs);


	_fmode = _O_BINARY;
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);
	_setmode(_fileno(stderr), _O_BINARY);


	winansi_init();
}
