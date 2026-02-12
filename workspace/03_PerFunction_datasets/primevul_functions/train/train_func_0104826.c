static const char *pp_getenv(const Token *t, bool warn)
{
    const char *txt = tok_text(t);
    const char *v;
    char *buf = NULL;
    bool is_string = false;

    if (!t)
	return NULL;

    switch (t->type) {
    case TOK_ENVIRON:
	txt += 2;
	is_string = nasm_isquote(*txt);
	break;

    case TOK_STRING:
	is_string = true;
	break;

    case TOK_INTERNAL_STRING:
    case TOK_NAKED_STRING:
    case TOK_ID:
	is_string = false;
	break;

    default:
	return NULL;
    }

    if (is_string) {
	buf = nasm_strdup(txt);
	nasm_unquote_cstr(buf, NULL);
	txt = buf;
    }

    v = getenv(txt);
    if (warn && !v) {


	nasm_warn(WARN_ENVIRONMENT, "nonexistent environment variable `%s'", txt);
	v = "";
    }

    if (buf)
	nasm_free(buf);

    return v;
}
