_nc_infotocap(const char *cap GCC_UNUSED, const char *str, int const parameterized)
{
    int seenone = 0, seentwo = 0, saw_m = 0, saw_n = 0;
    const char *padding;
    const char *trimmed = 0;
    int in0, in1, in2;
    char ch1 = 0, ch2 = 0;
    char *bufptr = init_string();
    char octal[4];
    int len;
    int digits;
    bool syntax_error = FALSE;
    int myfix = 0;
    struct {
	int ch;
	int offset;
    } fixups[MAX_TC_FIXUPS];

    DEBUG_THIS(("_nc_infotocap params %d, %s", parameterized, str));


    padding = str + strlen(str) - 1;
    if (padding > str && *padding == '>') {
	if (*--padding == '/')
	    --padding;
	while (isdigit(UChar(*padding)) || *padding == '.' || *padding == '*')
	    padding--;
	if (padding > str && *padding == '<' && *--padding == '$')
	    trimmed = padding;
	padding += 2;

	while (isdigit(UChar(*padding)) || *padding == '.' || *padding == '*')
	    bufptr = save_char(bufptr, *padding++);
    }

    for (; !syntax_error &&
	 *str &&
	 ((trimmed == 0) || (str < trimmed)); str++) {
	int c1, c2;
	char *cp = 0;

	if (str[0] == '^') {
	    if (str[1] == '\0' || (str + 1) == trimmed) {
		bufptr = save_string(bufptr, "\\136");
		++str;
	    } else if (str[1] == '?') {


		bufptr = save_string(bufptr, "\\177");
		++str;
	    } else {
		bufptr = save_char(bufptr, *str++);
		bufptr = save_char(bufptr, *str);
	    }
	} else if (str[0] == '\\') {
	    if (str[1] == '\0' || (str + 1) == trimmed) {
		bufptr = save_string(bufptr, "\\134");
		++str;
	    } else if (str[1] == '^') {
		bufptr = save_string(bufptr, "\\136");
		++str;
	    } else if (str[1] == ',') {
		bufptr = save_char(bufptr, *++str);
	    } else {
		int xx1;

		bufptr = save_char(bufptr, *str++);
		xx1 = *str;
		if (_nc_strict_bsd) {

		    if (isoctal(UChar(xx1))) {
			int pad = 0;
			int xx2;
			int fix = 0;

			if (!isoctal(UChar(str[1])))
			    pad = 2;
			else if (str[1] && !isoctal(UChar(str[2])))
			    pad = 1;


			if (xx1 == '0'
			    && ((pad == 2) || (str[1] == '0'))
			    && ((pad >= 1) || (str[2] == '0'))) {
			    xx2 = '2';
			} else {
			    xx2 = '0';
			    pad = 0;
			}
			if (myfix < MAX_TC_FIXUPS) {
			    fix = 3 - pad;
			    fixups[myfix].ch = 0;
			    fixups[myfix].offset = (int) (bufptr
							  - my_string
							  - 1);
			}
			while (pad-- > 0) {
			    bufptr = save_char(bufptr, xx2);
			    if (myfix < MAX_TC_FIXUPS) {
				fixups[myfix].ch <<= 3;
				fixups[myfix].ch |= (xx2 - '0');
			    }
			    xx2 = '0';
			}
			if (myfix < MAX_TC_FIXUPS) {
			    int n;
			    for (n = 0; n < fix; ++n) {
				fixups[myfix].ch <<= 3;
				fixups[myfix].ch |= (str[n] - '0');
			    }
			    if (fixups[myfix].ch < 32) {
				++myfix;
			    }
			}
		    } else if (strchr("E\\nrtbf", xx1) == 0) {
			switch (xx1) {
			case 'e':
			    xx1 = 'E';
			    break;
			case 'l':
			    xx1 = 'n';
			    break;
			case 's':
			    bufptr = save_char(bufptr, '0');
			    bufptr = save_char(bufptr, '4');
			    xx1 = '0';
			    break;
			case ':':


			    bufptr = save_char(bufptr, '0');
			    bufptr = save_char(bufptr, '7');
			    xx1 = '2';
			    break;
			default:

			    _nc_SPRINTF(octal, _nc_SLIMIT(sizeof(octal))
					"%03o", UChar(xx1));
			    bufptr = save_char(bufptr, octal[0]);
			    bufptr = save_char(bufptr, octal[1]);
			    xx1 = octal[2];
			    break;
			}
		    }
		} else {
		    if (myfix < MAX_TC_FIXUPS && isoctal(UChar(xx1))) {
			bool will_fix = TRUE;
			int n;

			fixups[myfix].ch = 0;
			fixups[myfix].offset = (int) (bufptr - my_string - 1);
			for (n = 0; n < 3; ++n) {
			    if (isoctal(str[n])) {
				octal_fixup(myfix, str[n]);
			    } else {
				will_fix = FALSE;
				break;
			    }
			}
			if (will_fix && (fixups[myfix].ch < 32))
			    ++myfix;
		    }
		}
		bufptr = save_char(bufptr, xx1);
	    }
	} else if (str[0] == '$' && str[1] == '<') {
	    str += 2;
	    while (isdigit(UChar(*str))
		   || *str == '.'
		   || *str == '*'
		   || *str == '/'
		   || *str == '>')
		str++;
	    --str;
	} else if (sscanf(str,
			  "[%%?%%p1%%{8}%%<%%t%d%%p1%%d%%e%%p1%%{16}%%<%%t%d%%p1%%{8}%%-%%d%%e%d;5;%%p1%%d%%;m",
			  &in0, &in1, &in2) == 3
		   && ((in0 == 4 && in1 == 10 && in2 == 48)
		       || (in0 == 3 && in1 == 9 && in2 == 38))) {

	    if ((str = strstr(str, ";m")) == 0)
		break;
	    ++str;
	    if (in2 == 48) {
		bufptr = save_string(bufptr, "[48;5;%dm");
	    } else {
		bufptr = save_string(bufptr, "[38;5;%dm");
	    }
	} else if (str[0] == '%' && str[1] == '%') {
	    bufptr = save_string(bufptr, "%%");
	    ++str;
	} else if (*str != '%' || (parameterized < 1)) {
	    bufptr = save_char(bufptr, *str);
	} else if (sscanf(str, "%%?%%{%d}%%>%%t%%{%d}%%+%%;", &c1, &c2) == 2) {
	    str = strchr(str, ';');
	    bufptr = save_tc_inequality(bufptr, c1, c2);
	} else if (sscanf(str, "%%?%%{%d}%%>%%t%%'%c'%%+%%;", &c1, &ch2) == 2) {
	    str = strchr(str, ';');
	    bufptr = save_tc_inequality(bufptr, c1, ch2);
	} else if (sscanf(str, "%%?%%'%c'%%>%%t%%{%d}%%+%%;", &ch1, &c2) == 2) {
	    str = strchr(str, ';');
	    bufptr = save_tc_inequality(bufptr, ch1, c2);
	} else if (sscanf(str, "%%?%%'%c'%%>%%t%%'%c'%%+%%;", &ch1, &ch2) == 2) {
	    str = strchr(str, ';');
	    bufptr = save_tc_inequality(bufptr, ch1, ch2);
	} else if ((len = bcd_expression(str)) != 0) {
	    str += len;
	    bufptr = save_string(bufptr, "%B");
	} else if ((sscanf(str, "%%{%d}%%+%%%c", &c1, &ch2) == 2
		    || sscanf(str, "%%'%c'%%+%%%c", &ch1, &ch2) == 2)
		   && ch2 == 'c'
		   && (cp = strchr(str, '+'))) {
	    str = cp + 2;
	    bufptr = save_string(bufptr, "%+");

	    if (ch1)
		c1 = ch1;
	    bufptr = save_tc_char(bufptr, c1);
	}

	else if (strncmp(str, "%{2}%*%-", (size_t) 8) == 0) {
	    str += 7;
	    bufptr = save_string(bufptr, "%D");
	} else if (strncmp(str, "%{96}%^", (size_t) 7) == 0) {
	    str += 6;
	    if (saw_m++ == 0) {
		bufptr = save_string(bufptr, "%n");
	    }
	} else if (strncmp(str, "%{127}%^", (size_t) 8) == 0) {
	    str += 7;
	    if (saw_n++ == 0) {
		bufptr = save_string(bufptr, "%m");
	    }
	} else {
	    str++;
	    switch (*str) {
	    case '%':
		bufptr = save_char(bufptr, '%');
		break;

	    case '0':
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
		bufptr = save_char(bufptr, '%');
		ch1 = 0;
		ch2 = 0;
		digits = 0;
		while (isdigit(UChar(*str))) {
		    if (++digits > 2) {
			syntax_error = TRUE;
			break;
		    }
		    ch2 = ch1;
		    ch1 = *str++;
		    if (digits == 2 && ch2 != '0') {
			syntax_error = TRUE;
			break;
		    } else if (_nc_strict_bsd) {
			if (ch1 > '3') {
			    syntax_error = TRUE;
			    break;
			}
		    } else {
			bufptr = save_char(bufptr, ch1);
		    }
		}
		if (syntax_error)
		    break;


		if (ch2 == '0' && !_nc_strict_bsd) {
		    ch2 = 0;
		    bufptr[-2] = bufptr[-1];
		    *--bufptr = 0;
		}
		if (_nc_strict_bsd) {
		    if (ch2 != 0 && ch2 != '0') {
			syntax_error = TRUE;
		    } else if (ch1 < '2') {
			ch1 = 'd';
		    }
		    bufptr = save_char(bufptr, ch1);
		}
		if (strchr("oxX.", *str)) {
		    syntax_error = TRUE;
		}
		break;

	    case 'd':
		bufptr = save_string(bufptr, "%d");
		break;

	    case 'c':
		bufptr = save_string(bufptr, "%.");
		break;


	    case 's':
		if (_nc_strict_bsd) {
		    syntax_error = TRUE;
		} else {
		    bufptr = save_string(bufptr, "%s");
		}
		break;

	    case 'p':
		str++;
		if (*str == '1')
		    seenone = 1;
		else if (*str == '2') {
		    if (!seenone && !seentwo) {
			bufptr = save_string(bufptr, "%r");
			seentwo++;
		    }
		} else if (*str >= '3') {
		    syntax_error = TRUE;
		}
		break;

	    case 'i':
		bufptr = save_string(bufptr, "%i");
		break;

	    default:
		bufptr = save_char(bufptr, *str);
		syntax_error = TRUE;
		break;
	    }
	}


	assert(str != 0);
	if (str == 0 || *str == '\0')
	    break;

    }

    if (!syntax_error &&
	myfix > 0 &&
	((int) strlen(my_string) - (4 * myfix)) < MIN_TC_FIXUPS) {
	while (--myfix >= 0) {
	    char *p = fixups[myfix].offset + my_string;
	    *p++ = '^';
	    *p++ = (char) (fixups[myfix].ch | '@');
	    while ((p[0] = p[2]) != '\0') {
		++p;
	    }
	}
    }

    DEBUG_THIS(("... _nc_infotocap %s",
		syntax_error
		? "<ERR>"
		: _nc_visbuf(my_string)));

    return (syntax_error ? NULL : my_string);
}
