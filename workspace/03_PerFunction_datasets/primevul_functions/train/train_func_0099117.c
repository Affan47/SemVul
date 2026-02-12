initvar(void)
{
	int i = 0;
	struct tbl *tp;

	ktinit(APERM, &specials,

	    5);
	while (i < V_MAX - 1) {
		tp = ktenter(&specials, initvar_names[i],
		    hash(initvar_names[i]));
		tp->flag = DEFINED|ISSET;
		tp->type = ++i;
	}
}
