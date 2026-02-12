initoptions_init()
{
#if defined(UNIX) || defined(VMS)
	char *opts;
#endif
	int i;


	reset_commands(TRUE);


	setrandom();


	iflags.opt_booldup = iflags.opt_compdup = (int *)0;

	for (i = 0; boolopt[i].name; i++) {
		if (boolopt[i].addr)
			*(boolopt[i].addr) = boolopt[i].initvalue;
	}
#if defined(COMPRESS) || defined(ZLIB_COMP)
	set_savepref("externalcomp");
	set_restpref("externalcomp");
# ifdef RLECOMP
	set_savepref("!rlecomp");
	set_restpref("!rlecomp");
# endif
#else
# ifdef ZEROCOMP
	set_savepref("zerocomp");
	set_restpref("zerocomp");
# endif
# ifdef RLECOMP
	set_savepref("rlecomp");
	set_restpref("rlecomp");
# endif
#endif
#ifdef SYSFLAGS
	Strcpy(sysflags.sysflagsid, "sysflags");
	sysflags.sysflagsid[9] = (char)sizeof(struct sysflag);
#endif
	flags.end_own = FALSE;
	flags.end_top = 3;
	flags.end_around = 2;
	flags.paranoia_bits = PARANOID_PRAY;
	flags.pile_limit = PILE_LIMIT_DFLT;
	flags.runmode = RUN_LEAP;
	iflags.msg_history = 20;
#ifdef TTY_GRAPHICS
	iflags.prevmsg_window = 's';
#  if defined(UNIX) && defined(UNICODE_WIDEWINPORT)
	iflags.unicodecapable = TRUE;
#  endif
#endif
	iflags.menu_headings = ATR_INVERSE;


	flags.initrole = flags.initrace =
	    flags.initgend = flags.initalign = ROLE_NONE;


	init_symbols();
	for (i = 0; i < WARNCOUNT; i++)
		warnsyms[i] = def_warnsyms[i].sym;
	iflags.bouldersym = 0;

	iflags.travelcc.x = iflags.travelcc.y = -1;


	(void)memcpy((genericptr_t)flags.inv_order,
		     (genericptr_t)def_inv_order, sizeof flags.inv_order);
	flags.pickup_types[0] = '\0';
	flags.pickup_burden = MOD_ENCUMBER;

	for (i = 0; i < NUM_DISCLOSURE_OPTIONS; i++)
		flags.end_disclose[i] = DISCLOSE_PROMPT_DEFAULT_NO;
	switch_symbols(FALSE);
#if defined(UNIX) && defined(TTY_GRAPHICS)


	if ((opts = nh_getenv("TERM")) && !strncmp(opts, "AT", 2)) {
#ifdef LOADSYMSETS
		if (!symset[PRIMARY].name) load_symset("IBMGraphics", PRIMARY);
		if (!symset[ROGUESET].name) load_symset("RogueIBM", ROGUESET);
		switch_symbols(TRUE);
#endif
# ifdef TEXTCOLOR
		iflags.use_color = TRUE;
# endif
	}
#endif
#if defined(UNIX) || defined(VMS)
# ifdef TTY_GRAPHICS

	if ((opts = nh_getenv("TERM")) &&
	    !strncmpi(opts, "vt", 2) && AS && AE &&
	    index(AS, '\016') && index(AE, '\017')) {
#  ifdef LOADSYMSETS
		if (!symset[PRIMARY].name) load_symset("DECGraphics", PRIMARY);
		switch_symbols(TRUE);
#  endif
	}
# endif
#endif

#ifdef MAC_GRAPHICS_ENV
	if (!symset[PRIMARY].name) load_symset("MACGraphics", PRIMARY);
	switch_symbols(TRUE);
#endif
	flags.menu_style = MENU_FULL;


	objects[SLIME_MOLD].oc_name_idx = SLIME_MOLD;
	nmcpy(pl_fruit, OBJ_NAME(objects[SLIME_MOLD]), PL_FSIZ);
}
