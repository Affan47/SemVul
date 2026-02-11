parse_cmdline_2 (int argc, TCHAR **argv)
{
	int i;

	cfgfile_addcfgparam (0);
	for (i = 1; i < argc; i++) {
		if (_tcsncmp (argv[i], _T("-cfgparam="), 10) == 0) {
			cfgfile_addcfgparam (argv[i] + 10);
		} else if (_tcscmp (argv[i], _T("-cfgparam")) == 0) {
			if (i + 1 == argc)
				write_log (_T("Missing argument for '-cfgparam' option.\n"));
			else
				cfgfile_addcfgparam (argv[++i]);
		}
	}
}
