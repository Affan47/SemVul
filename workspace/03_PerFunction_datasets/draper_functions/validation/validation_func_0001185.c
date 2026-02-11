stripsnug(struct parse *p, struct re_guts *g)
{
	g->nstates = p->slen;
	g->strip = (sop *)cli_realloc((char *)p->strip, p->slen * sizeof(sop));
	if (g->strip == NULL) {
		SETERROR(REG_ESPACE);
		g->strip = p->strip;
	}
}
