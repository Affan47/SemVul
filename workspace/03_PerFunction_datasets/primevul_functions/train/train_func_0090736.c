parseoptions(opts, tinitial, tfrom_file)
register char *opts;
boolean tinitial, tfrom_file;
{
	register char *op;
	unsigned num;
	boolean negated, duplicate;
	int i;
	const char *fullname;

	initial = tinitial;
	from_file = tfrom_file;
	if ((op = index(opts, ',')) != 0) {
		*op++ = 0;
		parseoptions(op, initial, from_file);
	}
	if (strlen(opts) > BUFSZ/2) {
		badoption("option too long");
		return;
	}


	while (isspace(*opts)) opts++;
	op = eos(opts);
	while (--op >= opts && isspace(*op)) *op = '\0';

	if (!*opts) return;
	negated = FALSE;
	while ((*opts == '!') || !strncmpi(opts, "no", 2)) {
		if (*opts == '!') opts++; else opts += 2;
		negated = !negated;
	}


	if (match_optname(opts, "colour", 5, FALSE))
		Strcpy(opts, "color");


	if (match_optname(opts, "female", 3, FALSE)) {
		if (duplicate_opt_detection(opts,0))
			complain_about_duplicate(opts,0);
		if(!initial && flags.female == negated)
			pline("That is not anatomically possible.");
		else
			flags.initgend = flags.female = !negated;
		return;
	}

	if (match_optname(opts, "male", 4, FALSE)) {
		if (duplicate_opt_detection(opts,0))
			complain_about_duplicate(opts,0);
		if(!initial && flags.female != negated)
			pline("That is not anatomically possible.");
		else
			flags.initgend = flags.female = negated;
		return;
	}

#if defined(MICRO) && !defined(AMIGA)

	if (match_optname(opts, "IBM_", 4, FALSE)) {
		iflags.BIOS = !negated;
		return;
	}
#endif


	fullname = "align";
	if (match_optname(opts, fullname, sizeof("align")-1, TRUE)) {
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0) {
			boolean val_negated = FALSE;
			while ((*op == '!') || !strncmpi(op, "no", 2)) {
				if (*op == '!') op++; else op += 2;
				val_negated = !val_negated;
			}
			if (val_negated) {
				if (!setrolefilter(op))
					badoption(opts);
			} else {
				if (duplicate_opt_detection(opts,1))
					complain_about_duplicate(opts,1);
				if ((flags.initalign = str2align(op)) == ROLE_NONE)
					badoption(opts);
			}
		}
		return;
	}


	fullname = "role";
	if (match_optname(opts, fullname, 4, TRUE) ||
	    match_optname(opts, (fullname = "character"), 4, TRUE)) {
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0) {
			boolean val_negated = FALSE;
			while ((*op == '!') || !strncmpi(op, "no", 2)) {
				if (*op == '!') op++; else op += 2;
				val_negated = !val_negated;
			}
			if (val_negated) {
				if (!setrolefilter(op))
					badoption(opts);
			} else {
				if (duplicate_opt_detection(opts,1))
					complain_about_duplicate(opts,1);
				if ((flags.initrole = str2role(op)) == ROLE_NONE)
					badoption(opts);
				else
					nmcpy(pl_character, op, PL_NSIZ);
			}
		}
		return;
	}


	fullname = "race";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0) {
			boolean val_negated = FALSE;
			while ((*op == '!') || !strncmpi(op, "no", 2)) {
				if (*op == '!') op++; else op += 2;
				val_negated = !val_negated;
			}
			if (val_negated) {
				if (!setrolefilter(op))
					badoption(opts);
			} else {
				if (duplicate_opt_detection(opts,1))
					complain_about_duplicate(opts,1);
				if ((flags.initrace = str2race(op)) == ROLE_NONE)
					badoption(opts);
				else
					pl_race = *op;
			}
		}
		return;
	}


	fullname = "gender";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0) {
			boolean val_negated = FALSE;
			while ((*op == '!') || !strncmpi(op, "no", 2)) {
				if (*op == '!') op++; else op += 2;
				val_negated = !val_negated;
			}
			if (val_negated) {
				if (!setrolefilter(op))
					badoption(opts);
			} else {
				if (duplicate_opt_detection(opts,1))
					complain_about_duplicate(opts,1);
				if ((flags.initgend = str2gend(op)) == ROLE_NONE)
					badoption(opts);
				else
					flags.female = flags.initgend;
			}
		}
		return;
	}


	duplicate = duplicate_opt_detection(opts,1);

	fullname = "pettype";
	if (match_optname(opts, fullname, 3, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if ((op = string_for_env_opt(fullname, opts, negated)) != 0) {
		    if (negated) bad_negation(fullname, TRUE);
		    else switch (lowc(*op)) {
			case 'd':
			    preferred_pet = 'd';
			    break;
			case 'c':
			case 'f':
			    preferred_pet = 'c';
			    break;
			case 'h':
			case 'q':


			    preferred_pet = 'h';
			    break;
			case 'n':
			    preferred_pet = 'n';
			    break;
			case '*':
			    preferred_pet = '\0';
			    break;
			default:
			    pline("Unrecognized pet type '%s'.", op);
			    break;
		    }
		} else if (negated) preferred_pet = 'n';
		return;
	}

	fullname = "catname";
	if (match_optname(opts, fullname, 3, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0)
			nmcpy(catname, op, PL_PSIZ);
		return;
	}

	fullname = "dogname";
	if (match_optname(opts, fullname, 3, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0)
			nmcpy(dogname, op, PL_PSIZ);
		return;
	}

	fullname = "horsename";
	if (match_optname(opts, fullname, 5, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0)
			nmcpy(horsename, op, PL_PSIZ);
		return;
	}

	fullname = "number_pad";
	if (match_optname(opts, fullname, 10, TRUE)) {
		boolean compat = (strlen(opts) <= 10);

		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, (compat || !initial));
		if (!op) {
		    if (compat || negated || initial) {


			iflags.num_pad = !negated;
			iflags.num_pad_mode = 0;
		    }
		} else if (negated) {
		    bad_negation("number_pad", TRUE);
		    return;
		} else {
		    int mode = atoi(op);

		    if (mode < -1 || mode > 4 || (mode == 0 && *op != '0')) {
			badoption(opts);
			return;
		    } else if (mode <= 0) {
			iflags.num_pad = FALSE;

			iflags.num_pad_mode = (mode < 0);
		    } else {
			iflags.num_pad = TRUE;
			iflags.num_pad_mode = 0;

			if (mode == 2 || mode == 4) iflags.num_pad_mode |= 1;

			if (mode == 3 || mode == 4) iflags.num_pad_mode |= 2;
		    }
		}
		reset_commands(FALSE);
		number_pad(iflags.num_pad ? 1 : 0);
		return;
	}

	fullname = "roguesymset";
	if (match_optname(opts, fullname, 7, TRUE)) {
#if defined(REINCARNATION) && defined(LOADSYMSETS)
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_opt(opts, FALSE)) != 0) {
		    symset[ROGUESET].name = (char *)alloc(strlen(op) + 1);
		    Strcpy(symset[ROGUESET].name, op);
		    if (!read_sym_file(ROGUESET)) {
		    	clear_symsetentry(ROGUESET, TRUE);
	    		raw_printf("Unable to load symbol set \"%s\" from \"%s\".",
					op, SYMBOLS);
			wait_synch();
		    } else {
			if (!initial && Is_rogue_level(&u.uz))
				assign_graphics(ROGUESET);
				need_redraw = TRUE;
		    }
		}
#endif
		return;
	}

	fullname = "symset";
	if (match_optname(opts, fullname, 6, TRUE)) {
#ifdef LOADSYMSETS
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_opt(opts, FALSE)) != 0) {
		    symset[PRIMARY].name = (char *)alloc(strlen(op) + 1);
		    Strcpy(symset[PRIMARY].name, op);
		    if (!read_sym_file(PRIMARY)) {
		    	clear_symsetentry(PRIMARY, TRUE);
	    		raw_printf("Unable to load symbol set \"%s\" from \"%s\".",
					op, SYMBOLS);
			wait_synch();
		    } else {
		    	switch_symbols(TRUE);
			need_redraw = TRUE;
		    }
		}
#endif
		return;
	}

	fullname = "runmode";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
		    flags.runmode = RUN_TPORT;
		} else if ((op = string_for_opt(opts, FALSE)) != 0) {
		    if (!strncmpi(op, "teleport", strlen(op)))
			flags.runmode = RUN_TPORT;
		    else if (!strncmpi(op, "run", strlen(op)))
			flags.runmode = RUN_LEAP;
		    else if (!strncmpi(op, "walk", strlen(op)))
			flags.runmode = RUN_STEP;
		    else if (!strncmpi(op, "crawl", strlen(op)))
			flags.runmode = RUN_CRAWL;
		    else
			badoption(opts);
		}
		return;
	}

	fullname = "msghistory";
	if (match_optname(opts, fullname, 3, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_env_opt(fullname, opts, negated);
		if ((negated && !op) || (!negated && op)) {
			iflags.msg_history = negated ? 0 : atoi(op);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}

	fullname="msg_window";

	if (match_optname(opts, fullname, 4, TRUE)) {

#ifdef TTY_GRAPHICS
		int tmp;
		if (duplicate) complain_about_duplicate(opts,1);
		if (!(op = string_for_opt(opts, TRUE))) {
		    tmp = negated ? 's' : 'f';
		} else {
		    if (negated) {
			bad_negation(fullname, TRUE);
			return;
		    }
		    tmp = tolower(*op);
		}
		switch (tmp) {
			case 's':
				iflags.prevmsg_window = 's';
				break;
			case 'c':
				iflags.prevmsg_window = 'c';
				break;
			case 'f':
				iflags.prevmsg_window = 'f';
				break;
			case 'r':
				iflags.prevmsg_window = 'r';
				break;
			default:
				badoption(opts);
		}
#endif
		return;
	}


	fullname = "font";
	if (!strncmpi(opts, fullname, 4)) {
		int opttype = -1;
		char *fontopts = opts + 4;

		if (!strncmpi(fontopts, "map", 3) ||
		    !strncmpi(fontopts, "_map", 4))
			opttype = MAP_OPTION;
		else if (!strncmpi(fontopts, "message", 7) ||
			 !strncmpi(fontopts, "_message", 8))
			opttype = MESSAGE_OPTION;
		else if (!strncmpi(fontopts, "text", 4) ||
			 !strncmpi(fontopts, "_text", 5))
			opttype = TEXT_OPTION;
		else if (!strncmpi(fontopts, "menu", 4) ||
			 !strncmpi(fontopts, "_menu", 5))
			opttype = MENU_OPTION;
		else if (!strncmpi(fontopts, "status", 6) ||
			 !strncmpi(fontopts, "_status", 7))
			opttype = STATUS_OPTION;
		else if (!strncmpi(fontopts, "_size", 5)) {
			if (!strncmpi(fontopts, "_size_map", 8))
				opttype = MAP_OPTION;
			else if (!strncmpi(fontopts, "_size_message", 12))
				opttype = MESSAGE_OPTION;
			else if (!strncmpi(fontopts, "_size_text", 9))
				opttype = TEXT_OPTION;
			else if (!strncmpi(fontopts, "_size_menu", 9))
				opttype = MENU_OPTION;
			else if (!strncmpi(fontopts, "_size_status", 11))
				opttype = STATUS_OPTION;
			else {
				badoption(opts);
				return;
			}
			if (duplicate) complain_about_duplicate(opts,1);
			if (opttype > 0 && !negated &&
			    (op = string_for_opt(opts, FALSE)) != 0) {
			    switch(opttype)  {
				case MAP_OPTION:
					iflags.wc_fontsiz_map = atoi(op);
					break;
				case MESSAGE_OPTION:
					iflags.wc_fontsiz_message = atoi(op);
					break;
				case TEXT_OPTION:
					iflags.wc_fontsiz_text = atoi(op);
					break;
				case MENU_OPTION:
					iflags.wc_fontsiz_menu = atoi(op);
					break;
				case STATUS_OPTION:
					iflags.wc_fontsiz_status = atoi(op);
					break;
			    }
			}
			return;
		} else {
			badoption(opts);
		}
		if (opttype > 0 &&
		    (op = string_for_opt(opts, FALSE)) != 0) {
			wc_set_font_name(opttype, op);
#ifdef MAC
			set_font_name (opttype, op);
#endif
			return;
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}
#ifdef CHANGE_COLOR
	if (match_optname(opts, "palette", 3, TRUE)
# ifdef MAC
	    || match_optname(opts, "hicolor", 3, TRUE)
# endif
							) {
	    int color_number, color_incr;

# ifndef WIN32CON
	    if (duplicate) complain_about_duplicate(opts,1);
# endif
# ifdef MAC
	    if (match_optname(opts, "hicolor", 3, TRUE)) {
		if (negated) {
		    bad_negation("hicolor", FALSE);
		    return;
		}
		color_number = CLR_MAX + 4;
		color_incr = -1;
	    } else {
# endif
		if (negated) {
		    bad_negation("palette", FALSE);
		    return;
		}
		color_number = 0;
		color_incr = 1;
# ifdef MAC
	    }
# endif
#ifdef WIN32CON
	    op = string_for_opt(opts, TRUE);
	    if (!alternative_palette(op))
		badoption(opts);
#else
	    if ((op = string_for_opt(opts, FALSE)) != (char *)0) {
		char *pt = op;
		int cnt, tmp, reverse;
		long rgb;

		while (*pt && color_number >= 0) {
		    cnt = 3;
		    rgb = 0L;
		    if (*pt == '-') {
			reverse = 1;
			pt++;
		    } else {
			reverse = 0;
		    }
		    while (cnt-- > 0) {
			if (*pt && *pt != '/') {
#  ifdef AMIGA
			    rgb <<= 4;
#  else
			    rgb <<= 8;
#  endif
			    tmp = *(pt++);
			    if (isalpha(tmp)) {
				tmp = (tmp + 9) & 0xf;
			    } else {
				tmp &= 0xf;
			    }
#  ifndef AMIGA

			    rgb += tmp << 4;
#  endif
			    rgb += tmp;
			}
		    }
		    if (*pt == '/') {
			pt++;
		    }
		    change_color(color_number, rgb, reverse);
		    color_number += color_incr;
		}
	    }
# endif
	    if (!initial) {
		need_redraw = TRUE;
	    }
	    return;
	}
#endif

	if (match_optname(opts, "fruit", 2, TRUE)) {
		char empty_str = '\0';
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if (negated) {
		    if (op) {
			bad_negation("fruit", TRUE);
			return;
		    }
		    op = &empty_str;
		    goto goodfruit;
		}
		if (!op) return;
		if (!initial) {
		    struct fruit *f;

		    num = 0;
		    for(f=ffruit; f; f=f->nextf) {
			if (!strcmp(op, f->fname)) goto goodfruit;
			num++;
		    }
		    if (num >= 100) {
			pline("Doing that so many times isn't very fruitful.");
			return;
		    }
		}
goodfruit:
		nmcpy(pl_fruit, op, PL_FSIZ);

		if (!*pl_fruit)
		    nmcpy(pl_fruit, "slime mold", PL_FSIZ);
		if (!initial) {
		    (void)fruitadd(pl_fruit);
		    pline("Fruit is now \"%s\".", pl_fruit);
		}


		return;
	}

	fullname = "warnings";
	if (match_optname(opts, fullname, 5, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else warning_opts(opts, fullname);
		return;
	}

#ifdef BACKWARD_COMPAT

	fullname = "boulder";
	if (match_optname(opts, fullname, 7, TRUE)) {
		int clash = 0;
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
		    bad_negation(fullname, FALSE);
		    return;
		}

		if (!(opts = string_for_opt(opts, FALSE)))
			return;
		escapes(opts, opts);
		if (def_char_to_monclass(opts[0]) != MAXMCLASSES)
			clash = 1;
		else if (opts[0] >= '1' && opts[0] <= '5')
			clash = 2;
		if (clash) {


			pline(
		  "Badoption - boulder symbol '%c' conflicts with a %s symbol.",
				opts[0], (clash == 1) ? "monster" : "warning");
		} else {


			iflags.bouldersym = (uchar) opts[0];
		}
		if (!initial) need_redraw = TRUE;
		return;
	}
#endif


	fullname = "name";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0)
			nmcpy(plname, op, PL_NSIZ);
		return;
	}


	fullname = "altkeyhandler";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) bad_negation(fullname, FALSE);
		else if ((op = string_for_opt(opts, negated))) {
#ifdef WIN32CON
		    (void)strncpy(iflags.altkeyhandler, op, MAX_ALTKEYHANDLER - 5);
		    load_keyboard_handler();
#endif
		}
		return;
	}


	fullname = "align_status";
	if (match_optname(opts, fullname, sizeof("align_status")-1, TRUE)) {
		op = string_for_opt(opts, negated);
		if (op && !negated) {
		    if (!strncmpi (op, "left", sizeof("left")-1))
			iflags.wc_align_status = ALIGN_LEFT;
		    else if (!strncmpi (op, "top", sizeof("top")-1))
			iflags.wc_align_status = ALIGN_TOP;
		    else if (!strncmpi (op, "right", sizeof("right")-1))
			iflags.wc_align_status = ALIGN_RIGHT;
		    else if (!strncmpi (op, "bottom", sizeof("bottom")-1))
			iflags.wc_align_status = ALIGN_BOTTOM;
		    else
			badoption(opts);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	fullname = "align_message";
	if (match_optname(opts, fullname, sizeof("align_message")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if (op && !negated) {
		    if (!strncmpi (op, "left", sizeof("left")-1))
			iflags.wc_align_message = ALIGN_LEFT;
		    else if (!strncmpi (op, "top", sizeof("top")-1))
			iflags.wc_align_message = ALIGN_TOP;
		    else if (!strncmpi (op, "right", sizeof("right")-1))
			iflags.wc_align_message = ALIGN_RIGHT;
		    else if (!strncmpi (op, "bottom", sizeof("bottom")-1))
			iflags.wc_align_message = ALIGN_BOTTOM;
		    else
			badoption(opts);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}

	fullname = "packorder";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
		    bad_negation(fullname, FALSE);
		    return;
		} else if (!(op = string_for_opt(opts, FALSE))) return;

		if (!change_inv_order(op))
			badoption(opts);
		return;
	}


	fullname = "paranoid_confirmation";
	if (match_optname(opts, fullname, 8, TRUE)) {


	    flags.paranoia_bits = 0;
	    if (negated) {
		flags.paranoia_bits = 0;
	    } else if ((op = string_for_opt(opts, TRUE)) != 0) {
		char *pp, buf[BUFSZ];

		op = mungspaces(strcpy(buf, op));
		for (;;) {


		    pp = index(op, ' ');
		    if (pp) *pp = '\0';


		    for (i = 0; i < SIZE(paranoia); ++i) {
			if (match_optname(op, paranoia[i].argname,
					  paranoia[i].argMinLen, FALSE) ||
			    (paranoia[i].synonym &&
				match_optname(op, paranoia[i].synonym,
					      paranoia[i].synMinLen, FALSE))) {
			    if (paranoia[i].flagmask)
				flags.paranoia_bits |= paranoia[i].flagmask;
			    else
				flags.paranoia_bits = 0;
			    break;
			}
		    }
		    if (i == SIZE(paranoia)) {


			badoption(opts);
			break;
		    }

		    if (pp) op = pp + 1;
		    else break;
		}
	    }
	    return;
	}


	fullname = "prayconfirm";
	if (match_optname(opts, fullname, 4, FALSE)) {
	    if (negated)
		flags.paranoia_bits &= ~PARANOID_PRAY;
	    else
		flags.paranoia_bits |= PARANOID_PRAY;
	    return;
	}


	fullname = "pickup_burden";
	if (match_optname(opts, fullname, 8, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
			bad_negation(fullname, FALSE);
			return;
		} else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0) {
		    switch (tolower(*op)) {

				case 'u':
					flags.pickup_burden = UNENCUMBERED;
					break;

				case 'b':
					flags.pickup_burden = SLT_ENCUMBER;
					break;

				case 's':
					flags.pickup_burden = MOD_ENCUMBER;
					break;

				case 'n':
					flags.pickup_burden = HVY_ENCUMBER;
					break;

				case 'o':
				case 't':
					flags.pickup_burden = EXT_ENCUMBER;
					break;

				case 'l':
					flags.pickup_burden = OVERLOADED;
					break;
				default:
				badoption(opts);
		    }
		}
		return;
	}


	if (match_optname(opts, "pickup_types", 8, TRUE)) {
		char ocl[MAXOCLASSES + 1], tbuf[MAXOCLASSES + 1],
		     qbuf[QBUFSZ], abuf[BUFSZ];
		int oc_sym;
		boolean badopt = FALSE, compat = (strlen(opts) <= 6), use_menu;

		if (duplicate) complain_about_duplicate(opts,1);
		oc_to_str(flags.pickup_types, tbuf);
		flags.pickup_types[0] = '\0';
		op = string_for_opt(opts, (compat || !initial));
		if (!op) {
		    if (compat || negated || initial) {


			flags.pickup = !negated;
			return;
		    }
		    oc_to_str(flags.inv_order, ocl);
		    use_menu = TRUE;
		    if (flags.menu_style == MENU_TRADITIONAL ||
			    flags.menu_style == MENU_COMBINATION) {
			use_menu = FALSE;
			Sprintf(qbuf, "New pickup_types: [%s am] (%s)",
				ocl, *tbuf ? tbuf : "all");
			getlin(qbuf, abuf);
			op = mungspaces(abuf);
			if (abuf[0] == '\0' || abuf[0] == '\033')
			    op = tbuf;
			else if (abuf[0] == 'm')
			    use_menu = TRUE;
		    }
		    if (use_menu) {
			(void) choose_classes_menu("Auto-Pickup what?", 1,
						   TRUE, ocl, tbuf);
			op = tbuf;
		    }
		}
		if (negated) {
		    bad_negation("pickup_types", TRUE);
		    return;
		}
		while (*op == ' ') op++;
		if (*op != 'a' && *op != 'A') {
		    num = 0;
		    while (*op) {
			oc_sym = def_char_to_objclass(*op);

			if (oc_sym != MAXOCLASSES &&
			    !index(flags.pickup_types, oc_sym)) {
			    flags.pickup_types[num] = (char)oc_sym;
			    flags.pickup_types[++num] = '\0';
			} else
			    badopt = TRUE;
			op++;
		    }
		    if (badopt) badoption(opts);
		}
		return;
	}


	fullname = "pile_limit";
	if (match_optname(opts, fullname, 4, TRUE)) {
	    if (duplicate) complain_about_duplicate(opts, 1);
	    op = string_for_opt(opts, negated);
	    if ((negated && !op) || (!negated && op))
		flags.pile_limit = negated ? 0 : atoi(op);
	    else if (negated)
		bad_negation(fullname, TRUE);
	    else
		flags.pile_limit = PILE_LIMIT_DFLT;

	    if (flags.pile_limit < 0) flags.pile_limit = PILE_LIMIT_DFLT;
	    return;
	}


	fullname = "playmode";
	if (match_optname(opts, fullname, 4, TRUE)) {
	    if (duplicate) complain_about_duplicate(opts, 1);
	    if (negated) bad_negation(fullname, FALSE);
	    if (duplicate || negated) return;
	    op = string_for_opt(opts, TRUE);
	    if (!strncmpi(op, "normal", 6) || !strcmpi(op, "play")) {
		wizard = discover = FALSE;
	    } else if (!strncmpi(op, "explore", 6) ||
		    !strncmpi(op, "discovery", 6)) {
		wizard = FALSE, discover = TRUE;
	    } else if (!strncmpi(op, "debug", 5) ||
		    !strncmpi(op, "wizard", 6)) {
#ifdef WIZARD
		wizard = TRUE, discover = FALSE;
#else
		raw_printf("\"%s\":%s -- debug mode not available.",
			   fullname, op);
#endif
	    } else {
		raw_printf("Invalid value for \"%s\":%s.", fullname, op);
	    }
	    return;
	}


	fullname = "player_selection";
	if (match_optname(opts, fullname, sizeof("player_selection")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if (op && !negated) {
		    if (!strncmpi(op, "dialog", sizeof("dialog")-1))
			iflags.wc_player_selection = VIA_DIALOG;
		    else if (!strncmpi(op, "prompt", sizeof("prompt")-1))
			iflags.wc_player_selection = VIA_PROMPTS;
		    else
			badoption(opts);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	if (match_optname(opts, "disclose", 7, TRUE)) {


		boolean badopt = FALSE;
		int idx, prefix_val;

		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, TRUE);
		if (op && negated) {
			bad_negation("disclose", TRUE);
			return;
		}


		if (!op || !strcmpi(op, "all") || !strcmpi(op, "none")) {
			if (op && !strcmpi(op, "none")) negated = TRUE;
			for (num = 0; num < NUM_DISCLOSURE_OPTIONS; num++)
			    flags.end_disclose[num] = negated ?
						DISCLOSE_NO_WITHOUT_PROMPT :
						DISCLOSE_PROMPT_DEFAULT_YES;
			return;
		}

		num = 0;
		prefix_val = -1;
		while (*op && num < sizeof flags.end_disclose - 1) {
			register char c, *dop;
			static char valid_settings[] = {
				DISCLOSE_PROMPT_DEFAULT_YES,
				DISCLOSE_PROMPT_DEFAULT_NO,
				DISCLOSE_YES_WITHOUT_PROMPT,
				DISCLOSE_NO_WITHOUT_PROMPT,
				'\0'
			};
			c = lowc(*op);
			if (c == 'k') c = 'v';
			dop = index(disclosure_options, c);
			if (dop) {
				idx = (int)(dop - disclosure_options);
				if (idx < 0 || idx > NUM_DISCLOSURE_OPTIONS - 1) {
				    impossible("bad disclosure index %d %c",
							idx, c);
				    continue;
				}
				if (prefix_val != -1) {
				    flags.end_disclose[idx] = prefix_val;
				    prefix_val = -1;
				} else
				    flags.end_disclose[idx] = DISCLOSE_YES_WITHOUT_PROMPT;
			} else if (index(valid_settings, c)) {
				prefix_val = c;
			} else if (c == ' ') {
				;
			} else
				badopt = TRUE;
			op++;
		}
		if (badopt) badoption(opts);
		return;
	}


	if (match_optname(opts, "scores", 4, TRUE)) {
	    if (duplicate) complain_about_duplicate(opts,1);
	    if (negated) {
		bad_negation("scores", FALSE);
		return;
	    }
	    if (!(op = string_for_opt(opts, FALSE))) return;

	    while (*op) {
		int inum = 1;

		if (digit(*op)) {
		    inum = atoi(op);
		    while (digit(*op)) op++;
		} else if (*op == '!') {
		    negated = !negated;
		    op++;
		}
		while (*op == ' ') op++;

		switch (*op) {
		 case 't':
		 case 'T':  flags.end_top = inum;
			    break;
		 case 'a':
		 case 'A':  flags.end_around = inum;
			    break;
		 case 'o':
		 case 'O':  flags.end_own = !negated;
			    break;
		 default:   badoption(opts);
			    return;
		}
		while (letter(*++op) || *op == ' ') continue;
		if (*op == '/') op++;
	    }
	    return;
	}

	fullname = "suppress_alert";
	if (match_optname(opts, fullname, 4, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if (negated) bad_negation(fullname, FALSE);
		else if (op) (void) feature_alert_opts(op,fullname);
		return;
	}

#ifdef VIDEOSHADES

	fullname = "videocolors";
	if (match_optname(opts, fullname, 6, TRUE) ||
	    match_optname(opts, "videocolours", 10, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
			bad_negation(fullname, FALSE);
			return;
		}
		else if (!(opts = string_for_env_opt(fullname, opts, FALSE))) {
			return;
		}
		if (!assign_videocolors(opts))
			badoption(opts);
		return;
	}

	fullname = "videoshades";
	if (match_optname(opts, fullname, 6, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
			bad_negation(fullname, FALSE);
			return;
		}
		else if (!(opts = string_for_env_opt(fullname, opts, FALSE))) {
			return;
		}
		if (!assign_videoshades(opts))
			badoption(opts);
		return;
	}
#endif
#ifdef MSDOS
# ifdef NO_TERMS

	fullname = "video";
	if (match_optname(opts, fullname, 5, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
			bad_negation(fullname, FALSE);
			return;
		}
		else if (!(opts = string_for_env_opt(fullname, opts, FALSE))) {
			return;
		}
		if (!assign_video(opts))
			badoption(opts);
		return;
	}
# endif

	fullname = "soundcard";
	if (match_optname(opts, fullname, 6, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
			bad_negation(fullname, FALSE);
			return;
		}
		else if (!(opts = string_for_env_opt(fullname, opts, FALSE))) {
			return;
		}
		if (!assign_soundcard(opts))
			badoption(opts);
		return;
	}
#endif


	fullname = "map_mode";
	if (match_optname(opts, fullname, sizeof("map_mode")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if (op && !negated) {
		    if (!strncmpi (op, "tiles", sizeof("tiles")-1))
			iflags.wc_map_mode = MAP_MODE_TILES;
		    else if (!strncmpi (op, "ascii4x6", sizeof("ascii4x6")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII4x6;
		    else if (!strncmpi (op, "ascii6x8", sizeof("ascii6x8")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII6x8;
		    else if (!strncmpi (op, "ascii8x8", sizeof("ascii8x8")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII8x8;
		    else if (!strncmpi (op, "ascii16x8", sizeof("ascii16x8")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII16x8;
		    else if (!strncmpi (op, "ascii7x12", sizeof("ascii7x12")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII7x12;
		    else if (!strncmpi (op, "ascii8x12", sizeof("ascii8x12")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII8x12;
		    else if (!strncmpi (op, "ascii16x12", sizeof("ascii16x12")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII16x12;
		    else if (!strncmpi (op, "ascii12x16", sizeof("ascii12x16")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII12x16;
		    else if (!strncmpi (op, "ascii10x18", sizeof("ascii10x18")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII10x18;
		    else if (!strncmpi (op, "fit_to_screen", sizeof("fit_to_screen")-1))
			iflags.wc_map_mode = MAP_MODE_ASCII_FIT_TO_SCREEN;
		    else
			badoption(opts);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	fullname = "scroll_amount";
	if (match_optname(opts, fullname, sizeof("scroll_amount")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if ((negated && !op) || (!negated && op)) {
			iflags.wc_scroll_amount = negated ? 1 : atoi(op);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	fullname = "scroll_margin";
	if (match_optname(opts, fullname, sizeof("scroll_margin")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if ((negated && !op) || (!negated && op)) {
			iflags.wc_scroll_margin = negated ? 5 : atoi(op);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}
	fullname = "subkeyvalue";
	if (match_optname(opts, fullname, 5, TRUE)) {

		if (negated) bad_negation(fullname, FALSE);
		else {
#if defined(WIN32CON)
			op = string_for_opt(opts, 0);
			map_subkeyvalue(op);
#endif
		}
		return;
	}


	fullname = "tile_width";
	if (match_optname(opts, fullname, sizeof("tile_width")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if ((negated && !op) || (!negated && op)) {
			iflags.wc_tile_width = negated ? 0 : atoi(op);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	fullname = "tile_file";
	if (match_optname(opts, fullname, sizeof("tile_file")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if ((op = string_for_opt(opts, FALSE)) != 0) {
			if (iflags.wc_tile_file) free(iflags.wc_tile_file);
			iflags.wc_tile_file = (char *)alloc(strlen(op) + 1);
			Strcpy(iflags.wc_tile_file, op);
		}
		return;
	}


	fullname = "tile_height";
	if (match_optname(opts, fullname, sizeof("tile_height")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if ((negated && !op) || (!negated && op)) {
			iflags.wc_tile_height = negated ? 0 : atoi(op);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	fullname = "vary_msgcount";
	if (match_optname(opts, fullname, sizeof("vary_msgcount")-1, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, negated);
		if ((negated && !op) || (!negated && op)) {
			iflags.wc_vary_msgcount = negated ? 0 : atoi(op);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}
	fullname = "windowtype";
	if (match_optname(opts, fullname, 3, TRUE)) {
	    if (duplicate) complain_about_duplicate(opts,1);
	    if (negated) {
		bad_negation(fullname, FALSE);
		return;
	    } else if ((op = string_for_env_opt(fullname, opts, FALSE)) != 0) {
		char buf[WINTYPELEN];
		nmcpy(buf, op, WINTYPELEN);
		choose_windows(buf);
	    }
	    return;
	}


	fullname = "windowcolors";
	if (match_optname(opts, fullname, 7, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if ((op = string_for_opt(opts, FALSE)) != 0) {
			if (!wc_set_window_colors(op))
				badoption(opts);
		} else if (negated) bad_negation(fullname, TRUE);
		return;
	}


	if (match_optname(opts, "menustyle", 4, TRUE)) {
		int tmp;
		boolean val_required = (strlen(opts) > 5 && !negated);

		if (duplicate) complain_about_duplicate(opts,1);
		if (!(op = string_for_opt(opts, !val_required))) {
		    if (val_required) return;
		    tmp = negated ? 'n' : 'f';
		} else {
		    tmp = tolower(*op);
		}
		switch (tmp) {
			case 'n':
			case 't':
				flags.menu_style = MENU_TRADITIONAL;
				break;
			case 'c':
				flags.menu_style = MENU_COMBINATION;
				break;
			case 'p':
				flags.menu_style = MENU_PARTIAL;
				break;
			case 'f':
				flags.menu_style = MENU_FULL;
				break;
			default:
				badoption(opts);
		}
		return;
	}

	fullname = "menu_headings";
	if (match_optname(opts, fullname, 12, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		if (negated) {
			bad_negation(fullname, FALSE);
			return;
		}
		else if (!(opts = string_for_env_opt(fullname, opts, FALSE))) {
			return;
		}
		if (!strcmpi(opts,"bold"))
			iflags.menu_headings = ATR_BOLD;
		else if (!strcmpi(opts,"inverse"))
			iflags.menu_headings = ATR_INVERSE;
		else if (!strcmpi(opts,"underline"))
			iflags.menu_headings = ATR_ULINE;
		else
			badoption(opts);
		return;
	}


	for (i = 0; i < NUM_MENU_CMDS; i++) {
	    fullname = default_menu_cmd_info[i].name;
	    if (duplicate) complain_about_duplicate(opts,1);
	    if (match_optname(opts, fullname, (int)strlen(fullname), TRUE)) {
		if (negated)
		    bad_negation(fullname, FALSE);
		else if ((op = string_for_opt(opts, FALSE)) != 0) {
		    int j;
		    char c, op_buf[BUFSZ];
		    boolean isbad = FALSE;

		    escapes(op, op_buf);
		    c = *op_buf;

		    if (c == 0 || c == '\r' || c == '\n' || c == '\033' ||
			    c == ' ' || digit(c) || (letter(c) && c != '@'))
			isbad = TRUE;
		    else
			for (j = 1; j < MAXOCLASSES; j++)
			    if (c == def_oc_syms[i].sym) {
				isbad = TRUE;
				break;
			    }

		    if (isbad)
			badoption(opts);
		    else
			add_menu_cmd_alias(c, default_menu_cmd_info[i].cmd);
		}
		return;
	    }
	}
#if defined(STATUS_VIA_WINDOWPORT) && defined(STATUS_HILITES)

	if (match_optname(opts, "hilite_status", 13, TRUE)) {
		if (duplicate) complain_about_duplicate(opts,1);
		op = string_for_opt(opts, TRUE);
		if (op && negated) {
			clear_status_hilites();
			return;
		} else if (!op) {

			badoption(opts);
			return;
		}
		if (!set_status_hilites(op))
			badoption(opts);
		return;
	}
#endif

#if defined(BACKWARD_COMPAT)
	fullname = "DECgraphics";
	if (match_optname(opts, fullname, 10, TRUE)) {
		boolean badflag = FALSE;
# ifdef LOADSYMSETS
		if (duplicate) complain_about_duplicate(opts,1);
		if (!negated) {

		    if (symset[PRIMARY].name)
			badflag = TRUE;
		    else {
			symset[PRIMARY].name = (char *)alloc(strlen(fullname) + 1);
			Strcpy(symset[PRIMARY].name, fullname);
			if (!read_sym_file(PRIMARY)) {
				badflag = TRUE;
				clear_symsetentry(PRIMARY, TRUE);
		        } else switch_symbols(TRUE);
		    }
		    if (badflag) {
		    	pline("Failure to load symbol set %s.",
		    		fullname);
			wait_synch();
		    }
		}
# endif
		return;
	}
	fullname = "IBMgraphics";
	if (match_optname(opts, fullname, 10, TRUE)) {
		const char *sym_name = fullname;
		boolean badflag = FALSE;
# ifdef LOADSYMSETS
		if (duplicate) complain_about_duplicate(opts,1);
		if (!negated) {
		    for (i = PRIMARY; i <= ROGUESET; ++i) {
			if (symset[i].name)
			    badflag = TRUE;
			else {
			    if (i == ROGUESET) sym_name = "RogueIBM";
			    symset[i].name = (char *)alloc(strlen(sym_name) + 1);
			    Strcpy(symset[i].name, sym_name);
			    if (!read_sym_file(i)) {
				badflag = TRUE;
				clear_symsetentry(i, TRUE);
				break;
			    }
			}
		    }
		    if (badflag) {
		    	pline("Failure to load symbol set %s.",
		    		sym_name);
			wait_synch();
		    } else {
			switch_symbols(TRUE);
#  ifdef REINCARNATION
			if (!initial && Is_rogue_level(&u.uz))
				assign_graphics(ROGUESET);
#  endif
		    }
		}
# endif
		return;
	}
#endif
#ifdef MAC_GRAPHICS_ENV
	fullname = "MACgraphics";
	if (match_optname(opts, fullname, 11, TRUE)) {
		boolean badflag = FALSE;
# ifdef LOADSYMSETS
		if (duplicate) complain_about_duplicate(opts,1);
		if (!negated) {
		    if (symset[PRIMARY]).name badflag = TRUE;
		    else {
			symset[PRIMARY].name = (char *)alloc(strlen(fullname) + 1);
			Strcpy(symset[PRIMARY].name, fullname);
			if (!read_sym_file(PRIMARY)) {
				badflag = TRUE;
				clear_symsetentry(PRIMARY, TRUE);
		        }
		    }
		    if (badflag) {
		    	pline("Failure to load symbol set %s.",
		    		fullname);
			wait_synch();
		    } else {
			switch_symbols(TRUE);
			if (!initial && Is_rogue_level(&u.uz))
				assign_graphics(ROGUESET);
		    }
		}
# endif
		return;
	}
#endif


	for (i = 0; boolopt[i].name; i++) {
		if (match_optname(opts, boolopt[i].name, 3, FALSE)) {


			if (!boolopt[i].addr) {
			    if (!initial && !negated)
				pline_The("\"%s\" option is not available.",
					boolopt[i].name);
			    return;
			}

			if (!initial && (boolopt[i].optflags == SET_IN_FILE)) {
			    rejectoption(boolopt[i].name);
			    return;
			}

			*(boolopt[i].addr) = !negated;


			if (duplicate_opt_detection(boolopt[i].name, 0))
			    complain_about_duplicate(boolopt[i].name,0);

#ifdef RLECOMP
			if ((boolopt[i].addr) == &iflags.rlecomp) {
				if (*boolopt[i].addr)
					set_savepref("rlecomp");
				else
					set_savepref("!rlecomp");
			}
#endif
#ifdef ZEROCOMP
			if ((boolopt[i].addr) == &iflags.zerocomp) {
				if (*boolopt[i].addr)
					set_savepref("zerocomp");
				else
					set_savepref("externalcomp");
			}
#endif

			if (initial) return;

			if ((boolopt[i].addr) == &flags.time
#ifdef EXP_ON_BOTL
			 || (boolopt[i].addr) == &flags.showexp
#endif
#ifdef SCORE_ON_BOTL
			 || (boolopt[i].addr) == &flags.showscore
#endif
			    ) {
#ifdef STATUS_VIA_WINDOWPORT
			    status_initialize(REASSESS_ONLY);
#endif
			    context.botl = TRUE;
			}
			else if ((boolopt[i].addr) == &flags.invlet_constant) {
			    if (flags.invlet_constant) reassign();
			}
			else if ((boolopt[i].addr) == &flags.lit_corridor) {


			    vision_recalc(2);
			    vision_full_recalc = 1;
			}
			else if ((boolopt[i].addr) == &iflags.use_inverse ||
					(boolopt[i].addr) == &flags.showrace ||
					(boolopt[i].addr) == &iflags.hilite_pet) {
			    need_redraw = TRUE;
			}
#ifdef TEXTCOLOR
			else if ((boolopt[i].addr) == &iflags.use_color) {
			    need_redraw = TRUE;
# ifdef TOS
			    if ((boolopt[i].addr) == &iflags.use_color
				&& iflags.BIOS) {
				if (colors_changed)
				    restore_colors();
				else
				    set_colors();
			    }
# endif
			}
#endif

			return;
		}
	}


	badoption(opts);
}
