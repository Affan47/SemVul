newedge(Agnode_t *t, char *tport, Agnode_t *h, char *hport, char *key)
{
	Agedge_t 	*e;

	e = agedge(S->g,t,h,key,TRUE);
	if (e) {
		char    *tp = tport;
		char    *hp = hport;
		if ((agtail(e) != aghead(e)) && (aghead(e) == t)) {

			char    *temp;
			temp = tp; tp = hp; hp = temp;
		}
		mkport(e,TAILPORT_ID,tp);
		mkport(e,HEADPORT_ID,hp);
		applyattrs(e);
	}
}
