set_array(const char *var, bool reset, const char **vals)
{
	struct tbl *vp, *vq;
	mksh_uari_t i = 0, j = 0;
	const char *ccp = var;
	char *cp = NULL;
	size_t n;


	n = strlen(var);
	if (n > 0 && var[n - 1] == '+') {

		reset = false;
		strndupx(cp, var, n - 1, ATEMP);
		ccp = cp;
	}
	vp = global(ccp);


	if ((vp->flag&RDONLY))
		errorfx(2, "read-only: %s", ccp);

	if (reset) {

		unset(vp, 1);

		arraysearch(vp, 0);
	}


	if (cp != NULL) {

		for (vq = vp; vq; vq = vq->u.array) {
			if (!(vq->flag & ISSET))
				continue;
			if (arrayindex(vq) >= j)
				j = arrayindex(vq) + 1;
		}
		afree(cp, ATEMP);
	}
	while ((ccp = vals[i])) {
#if 0
		if (*ccp == '[') {
			int level = 0;

			while (*ccp) {
				if (*ccp == ']' && --level == 0)
					break;
				if (*ccp == '[')
					++level;
				++ccp;
			}
			if (*ccp == ']' && level == 0 && ccp[1] == '=') {
				strndupx(cp, vals[i] + 1, ccp - (vals[i] + 1),
				    ATEMP);
				evaluate(substitute(cp, 0), (mksh_ari_t *)&j,
				    KSH_UNWIND_ERROR, true);
				afree(cp, ATEMP);
				ccp += 2;
			} else
				ccp = vals[i];
		}
#endif

		vq = arraysearch(vp, j);

		setstr(vq, ccp, KSH_RETURN_ERROR);
		i++;
		j++;
	}

	return (i);
}
