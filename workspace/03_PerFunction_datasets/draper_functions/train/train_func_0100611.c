overwrite_const_check (const char *s, parser *p)
{
    if (object_is_const(s)) {
	p->err = overwrite_err(s);
	return p->err;
    } else {
	return 0;
    }
}
