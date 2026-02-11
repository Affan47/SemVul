init_gtk(int argc, char **argv)
{
	int i, ok;
	game_saved = FALSE;
	toolbar_size = 0;


	ok = gtk_init_check(&argc, &argv);
	if (ok == FALSE) return -1;


	for (i = 1; i < argc; i++)
	{
		if (prefix(argv[i], "-n"))
		{
			num_term = atoi(&argv[i][2]);
			if (num_term > MAX_TERM_DATA) num_term = MAX_TERM_DATA;
			else if (num_term < 1) num_term = 1;
			continue;
		}

		if (prefix(argv[i], "-i"))
		{
			gtk_log_fmt(TERM_VIOLET, "Ignoring preferences.");
			ignore_prefs = TRUE;
			continue;
		}

		gtk_log_fmt(TERM_VIOLET, "Ignoring option: %s", argv[i]);
	}


	for (i = 0; i < MAX_XTRA_WIN_DATA; i++)
	{
		xtra_win_data *xd = &xdata[i];

		xtra_data_init(xd, i);
	}


	for (i = 0; i < num_term; i++)
	{
		term_data *td = &data[i];


		term_data_init(td, i);


		angband_term[i] = Term;
	}


	create_needed_dirs();


	load_prefs();


	init_gtk_windows();


	init_xtra_windows();


	show_windows();


	init_handlers();

	Term_activate(&data[0].t);


	ANGBAND_SYS = "gtk";


	#ifndef GTK_DEBUG
	signals_init();
	#endif


	prt("[Choose 'New' or 'Open' from the 'File' menu]", 23, 17);

	Term_fresh();
	game_in_progress = FALSE;


	init_display();


	play_game();


	cleanup_angband();
	quit(NULL);
	exit(0);


	return (0);
}
