tparam_internal(const char *string, TPARM_DATA * data)
{
    int number;
    int len;
    int level;
    int x, y;
    int i;
    const char *cp = string;
    size_t len2 = strlen(cp);
    bool incremented_two = FALSE;
    bool termcap_hack = tparm_tc_compat(data);

    tparm_trace_call(string, data);

    while ((cp - string) < (int) len2) {
	if (*cp != '%') {
	    save_char(UChar(*cp));
	} else {
	    TPS(tparam_base) = cp++;
	    cp = parse_format(cp, TPS(fmt_buff), &len);
	    switch (*cp) {
	    default:
		break;
	    case '%':
		save_char('%');
		break;

	    case 'd':
	    case 'o':
	    case 'x':
	    case 'X':
		save_number(TPS(fmt_buff), npop(), len);
		break;

	    case 'c':
		save_char(npop());
		break;

#ifdef EXP_XTERM_1005
	    case 'u':
		{
		    unsigned char target[10];
		    unsigned source = (unsigned) npop();
		    int rc = _nc_conv_to_utf8(target, source, (unsigned)
					      sizeof(target));
		    int n;
		    for (n = 0; n < rc; ++n) {
			save_char(target[n]);
		    }
		}
		break;
#endif
	    case 'l':
		npush((int) strlen(spop()));
		break;

	    case 's':
		save_text(TPS(fmt_buff), spop(), len);
		break;

	    case 'p':
		cp++;
		i = (UChar(*cp) - '1');
		if (i >= 0 && i < NUM_PARM) {
		    if (data->p_is_s[i]) {
			spush(data->p_is_s[i]);
		    } else {
			npush((int) data->param[i]);
		    }
		}
		break;

	    case 'P':
		cp++;
		if (isUPPER(*cp)) {
		    i = (UChar(*cp) - 'A');
		    TPS(static_vars)[i] = npop();
		} else if (isLOWER(*cp)) {
		    i = (UChar(*cp) - 'a');
		    TPS(dynamic_var)[i] = npop();
		}
		break;

	    case 'g':
		cp++;
		if (isUPPER(*cp)) {
		    i = (UChar(*cp) - 'A');
		    npush(TPS(static_vars)[i]);
		} else if (isLOWER(*cp)) {
		    i = (UChar(*cp) - 'a');
		    npush(TPS(dynamic_var)[i]);
		}
		break;

	    case S_QUOTE:
		cp++;
		npush(UChar(*cp));
		cp++;
		break;

	    case L_BRACE:
		number = 0;
		cp++;
		while (isdigit(UChar(*cp))) {
		    number = (number * 10) + (UChar(*cp) - '0');
		    cp++;
		}
		npush(number);
		break;

	    case '+':
		npush(npop() + npop());
		break;

	    case '-':
		y = npop();
		x = npop();
		npush(x - y);
		break;

	    case '*':
		npush(npop() * npop());
		break;

	    case '/':
		y = npop();
		x = npop();
		npush(y ? (x / y) : 0);
		break;

	    case 'm':
		y = npop();
		x = npop();
		npush(y ? (x % y) : 0);
		break;

	    case 'A':
		y = npop();
		x = npop();
		npush(y && x);
		break;

	    case 'O':
		y = npop();
		x = npop();
		npush(y || x);
		break;

	    case '&':
		npush(npop() & npop());
		break;

	    case '|':
		npush(npop() | npop());
		break;

	    case '^':
		npush(npop() ^ npop());
		break;

	    case '=':
		y = npop();
		x = npop();
		npush(x == y);
		break;

	    case '<':
		y = npop();
		x = npop();
		npush(x < y);
		break;

	    case '>':
		y = npop();
		x = npop();
		npush(x > y);
		break;

	    case '!':
		npush(!npop());
		break;

	    case '~':
		npush(~npop());
		break;

	    case 'i':


		if (!incremented_two) {
		    incremented_two = TRUE;
		    if (data->p_is_s[0] == 0) {
			data->param[0]++;
			if (termcap_hack)
			    TPS(stack)[0].data.num = (int) data->param[0];
		    }
		    if (data->p_is_s[1] == 0) {
			data->param[1]++;
			if (termcap_hack)
			    TPS(stack)[1].data.num = (int) data->param[1];
		    }
		}
		break;

	    case '?':
		break;

	    case 't':
		x = npop();
		if (!x) {

		    cp++;
		    level = 0;
		    while (*cp) {
			if (*cp == '%') {
			    cp++;
			    if (*cp == '?')
				level++;
			    else if (*cp == ';') {
				if (level > 0)
				    level--;
				else
				    break;
			    } else if (*cp == 'e' && level == 0)
				break;
			}

			if (*cp)
			    cp++;
		    }
		}
		break;

	    case 'e':

		cp++;
		level = 0;
		while (*cp) {
		    if (*cp == '%') {
			cp++;
			if (*cp == '?')
			    level++;
			else if (*cp == ';') {
			    if (level > 0)
				level--;
			    else
				break;
			}
		    }

		    if (*cp)
			cp++;
		}
		break;

	    case ';':
		break;

	    }
	}

	if (*cp == '\0')
	    break;

	cp++;
    }

    get_space((size_t) 1);
    TPS(out_buff)[TPS(out_used)] = '\0';

    T((T_RETURN("%s"), _nc_visbuf(TPS(out_buff))));
    return (TPS(out_buff));
}
