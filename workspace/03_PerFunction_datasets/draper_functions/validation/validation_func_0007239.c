main (argc, argv)
    int		argc;
    char *	argv[];
    {
    char *	argp;
    char *	preftype = NULL;
    char *	wchars = NULL;

    while (argc > 1  &&  argv[1][0] == '-')
	{
	argc--;
	argv++;
	switch (argv[0][1])
	    {
	    case 'T':
		argp = (*argv)+2;
		if (*argp == '\0')
		    {
		    argv++; argc--;
		    if (argc == 0)
			usage ();
		    argp = *argv;
		    }
		preftype = argp;
		break;
	    case 'w':
		wchars = (*argv) + 2;
		if (*wchars == '\0')
		    {
		    argv++;
		    argc--;
		    if (argc == 0)
			usage ();
		    wchars = *argv;
		    }
		break;
		break;
	    default:
		usage ();
		break;
	    }
	}

    if (argc > 1)
	Lfile = argv[1];
    else
	Lfile = DEFLANG;

    if (yyopen (Lfile))
      return 1;
    yyinit ();
    if (yyparse ())
	exit (1);

    initckch (wchars);

    if (preftype != NULL)
	{
	defstringgroup = findfiletype (preftype, 1, (int *) NULL);
	if (defstringgroup < 0
	  &&  strcmp (preftype, "plain") != 0
	  &&  strcmp (preftype, "tex") != 0
	  &&  strcmp (preftype, "nroff") != 0
	  &&  strcmp (preftype, "sgml") != 0)
	    {
	    (void) fprintf (stderr, ICOMBINE_C_BAD_TYPE, preftype);
	    exit (1);
	    }
	}
    if (defstringgroup < 0)
	defstringgroup = 0;

    combinedict ();

    return 0;
    }
