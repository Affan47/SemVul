static struct SYMBOL *get_info(struct SYMBOL *s)
{
	struct SYMBOL *s2;
	struct VOICE_S *p_voice;
	char *p;
	char info_type;
	int old_lvl;
	static char *state_txt[] = {"global", "header", "tune"};


	old_lvl = lvlarena(s->state != ABC_S_GLOBAL);

	info_type = s->text[0];
	switch (info_type) {
	case 'd':
		break;
	case 'I':
		s = process_pscomment(s);
		break;
	case 'K':
		get_key(s);
		if (s->state != ABC_S_HEAD)
			break;
		info['K' - 'A'] = s;
		tunenum++;

		if (!epsf) {


			bskip(cfmt.topspace);
		}
		a2b("%% --- xref %s\n", &info['X' - 'A']->text[2]);
		write_heading();
		block_put();


		s2 = info['T' - 'A'];
		p = &s2->text[2];
		if (*p != '\0') {
			a2b("%% --- font ");
			outft = -1;
			set_font(TITLEFONT);
			a2b("\n");
			outft = -1;
		}
		if (cfmt.pdfmark) {
			if (*p != '\0')
				put_pdfmark(p);
			if (cfmt.pdfmark > 1) {
				for (s2 = s2->next; s2; s2 = s2->next) {
					p = &s2->text[2];
					if (*p != '\0')
						put_pdfmark(p);
				}
			}
		}

		nbar = cfmt.measurefirst;
		over_voice = -1;
		over_time = -1;
		over_bar = 0;
		capo = 0;
		reset_gen();

		s = get_global_def(s);

		if (!(cfmt.fields[0] & (1 << ('Q' - 'A'))))
			info['Q' - 'A'] = NULL;


		voice_filter();


		if (!first_voice->tblts[0])
			set_tblt(first_voice);
		break;
	case 'L':
		switch (s->state) {
		case ABC_S_HEAD: {
			int i, auto_len;

			auto_len = s->u.length.base_length < 0;

			for (i = MAXVOICE, p_voice = voice_tb;
			     --i >= 0;
			     p_voice++)
				p_voice->auto_len = auto_len;
			break;
		    }
		case ABC_S_TUNE:
			curvoice->auto_len = s->u.length.base_length < 0;
			break;
		}
		break;
	case 'M':
		get_meter(s);
		break;
	case 'P': {
		struct VOICE_S *curvoice_sav;

		if (s->state != ABC_S_TUNE) {
			info['P' - 'A'] = s;
			break;
		}

		if (!(cfmt.fields[0] & (1 << ('P' - 'A'))))
			break;


		p_voice = &voice_tb[parsys->top_voice];
		if (curvoice != p_voice) {
			if (curvoice->time != p_voice->time)
				break;
			if (p_voice->last_sym && p_voice->last_sym->type == PART)
				break;
			curvoice_sav = curvoice;
			curvoice = p_voice;
			sym_link(s, PART);
			curvoice = curvoice_sav;
			break;
		}
		sym_link(s, PART);
		break;
	    }
	case 'Q':
		if (!(cfmt.fields[0] & (1 << ('Q' - 'A'))))
			break;
		if (s->state != ABC_S_TUNE) {
			info['Q' - 'A'] = s;
			break;
		}
		if (curvoice != &voice_tb[parsys->top_voice])
			break;
		s2 = curvoice->last_sym;
		if (s2) {
			int tim;

			tim = s2->time;
			do {
				if (s2->type == TEMPO) {
					if (!s2->next)
						curvoice->last_sym = s2->prev;
					else
						s2->next->prev = s2->prev;
					if (!s2->prev)
						curvoice->sym = s2->next;
					else
						s2->prev->next = s2->next;
					break;
				}
				s2 = s2->prev;
			} while (s2 && s2->time == tim);
		}
		sym_link(s, TEMPO);
		break;
	case 'r':
	case 's':
		break;
	case 'T':
		if (s->state == ABC_S_GLOBAL)
			break;
		if (s->state == ABC_S_HEAD)
			goto addinfo;
		gen_ly(1);
		p = &s->text[2];
		if (*p != '\0') {
			write_title(s);
			a2b("%% --- + (%s) ---\n", p);
			if (cfmt.pdfmark)
				put_pdfmark(p);
		}
		voice_init();
		reset_gen();
		s = get_global_def(s);
		break;
	case 'U':
		deco[s->u.user.symbol] = parse.deco_tb[s->u.user.value - 128];
		break;
	case 'u':
		break;
	case 'V':
		get_voice(s);


		if (s->abc_next && s->abc_next->abc_type == ABC_T_CLEF) {
			s = s->abc_next;
			get_clef(s);
		}
		if (s->state == ABC_S_TUNE
		 && !curvoice->last_sym
		 && curvoice->time == 0)
			voice_filter();
		break;
	case 'w':
		if (s->state != ABC_S_TUNE)
			break;
		if (!(cfmt.fields[1] & (1 << ('w' - 'a')))) {
			while (s->abc_next) {
				if (s->abc_next->abc_type != ABC_T_INFO
				 || s->abc_next->text[0] != '+')
					break;
				s = s->abc_next;
			}
			break;
		}
		s = get_lyric(s);
		break;
	case 'W':
		if (s->state == ABC_S_GLOBAL
		 || !(cfmt.fields[0] & (1 << ('W' - 'A'))))
			break;
		goto addinfo;
	case 'X':
		if (!epsf) {
			buffer_eob(0);
			write_buffer();

			if (cfmt.oneperpage)
				close_page();

			else
				use_buffer = cfmt.splittune != 1;
		}

		memcpy(&dfmt, &cfmt, sizeof dfmt);
		memcpy(&info_glob, &info, sizeof info_glob);
		memcpy(deco_glob, deco, sizeof deco_glob);
		save_maps();
		info['X' - 'A'] = s;
		if (tune_opts)
			tune_filter(s);
		break;
	default:
		if (info_type >= 'A' && info_type <= 'Z') {
			struct SYMBOL *prev;

			if (s->state == ABC_S_TUNE)
				break;
addinfo:
			prev = info[info_type - 'A'];
			if (!prev
			 || (prev->state == ABC_S_GLOBAL
			  && s->state != ABC_S_GLOBAL)) {
				info[info_type - 'A'] = s;
			} else {
				while (prev->next)
					prev = prev->next;
				prev->next = s;
			}
			while (s->abc_next
			    && s->abc_next->abc_type == ABC_T_INFO
			    && s->abc_next->text[0] == '+') {
				prev = s;
				s = s->abc_next;
				prev->next = s;
			}
			s->prev = prev;
			break;
		}
		if (s->state != ABC_S_GLOBAL)
			error(1, s, "%s info '%c:' not treated",
				state_txt[(int) s->state], info_type);
		break;
	}
	lvlarena(old_lvl);
	return s;
}
