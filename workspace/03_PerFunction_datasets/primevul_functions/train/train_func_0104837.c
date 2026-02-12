static Token *tokenize(const char *line)
{
    enum pp_token_type type;
    Token *list = NULL;
    Token *t, **tail = &list;

    while (*line) {
        const char *p = line;
        const char *ep = NULL;
        size_t toklen;
        char firstchar = *p;

        if (*p == '%') {

            p++;
            if (*p == '+' && !nasm_isdigit(p[1])) {

                p++;
            } else if (nasm_isdigit(*p) ||
                       ((*p == '-' || *p == '+') && nasm_isdigit(p[1]))) {
                do {
                    p++;
                }
                while (nasm_isdigit(*p));
            } else if (*p == '{' || *p == '[') {

                char firstchar = *p;
                char endchar = *p + 2;
                int lvl = 1;
                line += (*p++ == '{');
                while (lvl) {
                    if (*p == firstchar) {
                        lvl++;
                    } else if (*p == endchar) {
                        lvl--;
                    } else if (nasm_isquote(*p)) {
                        p = nasm_skip_string(p);
                    }

                    if (!*p) {
                        nasm_warn(WARN_OTHER, "unterminated %%%c construct",
                                  firstchar);
                        break;
                    }
                    p++;
                }
                ep = lvl ? p : p-1;
            } else if (*p == '?') {

                p++;
                if (*p == '?')
                    p++;
            } else if (*p == '*' && p[1] == '?') {

                p += 2;
                if (*p == '?')
                    p++;
            } else if (*p == '!') {

                p++;
                if (nasm_isidchar(*p)) {
                    do {
                        p++;
                    }
                    while (nasm_isidchar(*p));
                } else if (nasm_isquote(*p)) {
                    p = nasm_skip_string(p);
                    if (*p)
                        p++;
                    else
                        nasm_nonfatalf(ERR_PASS1, "unterminated %%! string");
                } else {

                }
            } else if (*p == ',') {

                p++;
            } else if (nasm_isidchar(*p) ||
                       ((*p == '%' || *p == '$') && nasm_isidchar(p[1]))) {

                do {
                    p++;
                }
                while (nasm_isidchar(*p));
            } else if (*p == '%') {

                p++;
            }

            if (!ep)
                ep = p;
            toklen = ep - line;

            if (toklen < 2) {
                type = TOK_OTHER;
            } else {
                char c0 = line[1];

                switch (c0) {
                case '+':
                    type = (toklen == 2) ? TOK_PASTE : TOK_MMACRO_PARAM;
                    break;

                case '-':
                    type = TOK_MMACRO_PARAM;
                    break;

                case '?':
                    if (toklen == 2)
                        type = TOK_PREPROC_Q;
                    else if (toklen == 3 && line[2] == '?')
                        type = TOK_PREPROC_QQ;
                    else
                        type = TOK_PREPROC_ID;
                    break;

                case '*':
                    type = TOK_OTHER;
                    if (line[2] == '?') {
                        if (toklen == 3)
                            type = TOK_PREPROC_SQ;
                        else if (toklen == 4 && line[3] == '?')
                            type = TOK_PREPROC_SQQ;
                    }
                    break;

                case '!':
                    type = (toklen == 2) ? TOK_OTHER : TOK_ENVIRON;
                    break;

                case '%':
                    type = (toklen == 2) ? TOK_OTHER : TOK_LOCAL_SYMBOL;
                    break;

                case '$':
                    type = (toklen == 2) ? TOK_OTHER : TOK_LOCAL_MACRO;
                    break;

                case '[':
                    line += 2;
                    firstchar = *line;
                    toklen -= 2;
                    type = TOK_INDIRECT;
                    break;

                case ',':
                    type = (toklen == 2) ? TOK_COND_COMMA : TOK_PREPROC_ID;
                    break;

                case '\'':
                case '\"':
                case '`':

                    type = TOK_PREPROC_ID;
                    break;

                case ':':
                    type = TOK_MMACRO_PARAM;
                    break;

                default:
                    if (nasm_isdigit(c0))
                        type = TOK_MMACRO_PARAM;
                    else if (nasm_isidchar(c0) || toklen > 2)
                        type = TOK_PREPROC_ID;
                    else
                        type = TOK_OTHER;
                    break;
                }
            }
        } else if (nasm_isidstart(*p) || (*p == '$' && nasm_isidstart(p[1]))) {

            type = TOK_ID;
            while (nasm_isidchar(*++p))
                ;
         } else if (nasm_isquote(*p)) {

            type = TOK_STRING;
            p = nasm_skip_string(p);

            if (*p) {
                p++;
            } else {
                nasm_warn(WARN_OTHER, "unterminated string");

            }
        } else if (p[0] == '$' && p[1] == '$') {

            type = TOK_ID;
            p += 2;
        } else if (nasm_isnumstart(*p)) {
            bool is_hex = false;
            bool is_float = false;
            bool has_e = false;
            char c;

            if (*p == '$') {
                p++;
                is_hex = true;
            }

            for (;;) {
                c = *p++;

                if (!is_hex && (c == 'e' || c == 'E')) {
                    has_e = true;
                    if (*p == '+' || *p == '-') {

                        p++;
                        is_float = true;
                    }
                } else if (c == 'H' || c == 'h' || c == 'X' || c == 'x') {
                    is_hex = true;
                } else if (c == 'P' || c == 'p') {
                    is_float = true;
                    if (*p == '+' || *p == '-')
                        p++;
                } else if (nasm_isnumchar(c))
                    ;
                else if (c == '.') {

                    const char *r = p;
                    while (*r == '_')
                        r++;

                    if (nasm_isdigit(*r) || (is_hex && nasm_isxdigit(*r)) ||
                        (!is_hex && (*r == 'e' || *r == 'E')) ||
                        (*r == 'p' || *r == 'P')) {
                        p = r;
                        is_float = true;
                    } else
                        break;
                } else
                    break;
            }
            p--;

            if (p == line+1 && *line == '$') {

                type = TOK_ID;
            } else {
                if (has_e && !is_hex) {

                    is_float = true;
                }

                type = is_float ? TOK_FLOAT : TOK_NUMBER;
            }
        } else if (nasm_isspace(*p)) {
            type = TOK_WHITESPACE;
            p = nasm_skip_spaces(p);

            if (!*p || *p == ';') {
                type = TOK_COMMENT;
                while (*p)
                    p++;
            }
        } else if (*p == ';') {
            type = TOK_COMMENT;
            while (*p)
                p++;
        } else {

            type = TOK_OTHER;
	    switch (*p++) {
	    case '>':
		if (*p == '>') {
		    p++;
		    if (*p == '>')
			p++;
		} else if (*p == '=') {
                    p++;
                }
		break;

	    case '<':
		if (*p == '<') {
		    p++;
		    if (*p == '<')
			p++;
		} else if (*p == '=') {
		    p++;
		    if (*p == '>')
			p++;
		} else if (*p == '>') {
		    p++;
		}
		break;

	    case '!':
		if (*p == '=')
		    p++;
		break;

	    case '/':
	    case '=':
	    case '&':
	    case '|':
	    case '^':

		if (*p == p[-1])
		    p++;
		break;

	    default:
		break;
	    }
        }

        if (type == TOK_WHITESPACE) {
            *tail = t = new_White(NULL);
            tail = &t->next;
        } else if (type != TOK_COMMENT) {
            if (!ep)
                ep = p;
            *tail = t = new_Token(NULL, type, line, ep - line);
            *tok_text_buf(t) = firstchar;
            tail = &t->next;
        }
        line = p;
    }
    return list;
}
}
}
