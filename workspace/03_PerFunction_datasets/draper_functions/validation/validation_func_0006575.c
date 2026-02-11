rc_stringlist_new(void)
{
	RC_STRINGLIST *l = xmalloc(sizeof(*l));
	TAILQ_INIT(l);
	return l;
}
