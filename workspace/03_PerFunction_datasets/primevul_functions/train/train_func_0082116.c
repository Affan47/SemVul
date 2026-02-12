static Token *tokenize(char *line)
{
    char c, *p = line;
    enum pp_token_type type;
    Token *list = NULL;
    Token *t, **tail = &list;

    while (*line) {
        p = line;
        if (*p == '%') {
            p++;
            if (*p == '+' && !nasm_isdigit(p[1])) {
                p++;
                type = TOK_PASTE;
            } else if (nasm_isdigit(*p) ||
                       ((*p == '-' || *p == '+') && nasm_isdigit(p[1]))) {
                do {
                    p++;
                }
                while (nasm_isdigit(*p));
                type = TOK_PREPROC_ID;
            } else if (*p == '{') {
                p++;
                while (*p) {
                    if (*p == '}')
                        break;
                    p[-1] = *p;
                    p++;
                }
                if (*p != '}')
                    nasm_error(ERR_WARNING | ERR_PASS1,
			       "unterminated %%{ construct");
                p[-1] = '\0';
                if (*p)
                    p++;
                type = TOK_PREPROC_ID;
            } else if (*p == '[') {
                int lvl = 1;
                line += 2;
                p++;
                while (lvl && (c = *p++)) {
                    switch (c) {
                    case ']':
                        lvl--;
                        break;
                    case '%':
                        if (*p == '[')
                            lvl++;
                        break;
                    case '\'':
                    case '\"':
                    case '`':
                        p = nasm_skip_string(p - 1) + 1;
                        break;
                    default:
                        break;
                    }
                }
                p--;
                if (*p)
                    *p++ = '\0';
                if (lvl)
                    nasm_error(ERR_NONFATAL|ERR_PASS1,
			       "unterminated %%[ construct");
                type = TOK_INDIRECT;
            } else if (*p == '?') {
                type = TOK_PREPROC_Q;
                p++;
                if (*p == '?') {
                    type = TOK_PREPROC_QQ;
                    p++;
                }
            } else if (*p == '!') {
                type = TOK_PREPROC_ID;
                p++;
                if (isidchar(*p)) {
                    do {
                        p++;
                    }
                    while (isidchar(*p));
                } else if (*p == '\'' || *p == '\"' || *p == '`') {
                    p = nasm_skip_string(p);
                    if (*p)
                        p++;
                    else
                        nasm_error(ERR_NONFATAL|ERR_PASS1,
				   "unterminated %%! string");
                } else {

                    type = TOK_OTHER;
                }
            } else if (isidchar(*p) ||
                       ((*p == '!' || *p == '%' || *p == '$') &&
                        isidchar(p[1]))) {
                do {
                    p++;
                }
                while (isidchar(*p));
                type = TOK_PREPROC_ID;
            } else {
                type = TOK_OTHER;
                if (*p == '%')
                    p++;
            }
        } else if (isidstart(*p) || (*p == '$' && isidstart(p[1]))) {
            type = TOK_ID;
            p++;
            while (*p && isidchar(*p))
                p++;
        } else if (*p == '\'' || *p == '"' || *p == '`') {


            type = TOK_STRING;
            p = nasm_skip_string(p);

            if (*p) {
                p++;
            } else {
                nasm_error(ERR_WARNING|ERR_PASS1, "unterminated string");


            }
        } else if (p[0] == '$' && p[1] == '$') {
            type = TOK_OTHER;
            p += 2;
        } else if (isnumstart(*p)) {
            bool is_hex = false;
            bool is_float = false;
            bool has_e = false;
            char c, *r;


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
                } else if (isnumchar(c))
                    ;
                else if (c == '.') {


                    r = p;
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
                type = TOK_OTHER;
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
            if ((p[0] == '>' && p[1] == '>') ||
                (p[0] == '<' && p[1] == '<') ||
                (p[0] == '/' && p[1] == '/') ||
                (p[0] == '<' && p[1] == '=') ||
                (p[0] == '>' && p[1] == '=') ||
                (p[0] == '=' && p[1] == '=') ||
                (p[0] == '!' && p[1] == '=') ||
                (p[0] == '<' && p[1] == '>') ||
                (p[0] == '&' && p[1] == '&') ||
                (p[0] == '|' && p[1] == '|') ||
                (p[0] == '^' && p[1] == '^')) {
                p++;
            }
            p++;
        }


        if (type != TOK_COMMENT) {
            *tail = t = new_Token(NULL, type, line, p - line);
            tail = &t->next;
        }
        line = p;
    }
    return list;
}
