isgroupmember(gid)
g_id_t gid;
{
# ifdef	USEGETGROUPS
	gid_t *gidset;
	int n;
# else
	uidtable *up;
# endif
	gidtable *gp;
	int i;

	if (!(gp = findgid(gid, NULL))) return(0);
	if (!(gp -> ismem)) {
		gp -> ismem++;
# ifdef	USEGETGROUPS
		if ((n = getgroups(0, NULL)) > 0) {
			gidset = (gid_t *)Xmalloc(n * sizeof(*gidset));
			n = getgroups(n, gidset);
			for (i = 0; i < n; i++) {
				if (gidset[i] != (gid_t)(gp -> gid)) continue;
				gp -> ismem++;
				break;
			}
			Xfree(gidset);
		}
# else
		if (gp -> gr_mem && (up = finduid(geteuid(), NULL)))
		for (i = 0; gp -> gr_mem[i]; i++) {
			if (!strpathcmp(up -> name, gp -> gr_mem[i])) {
				gp -> ismem++;
				break;
			}
		}
		freevar(gp -> gr_mem);
		gp -> gr_mem = NULL;
# endif
	}

	return(gp -> ismem - 1);
}
