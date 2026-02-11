setvar(const char *name, const char *val, int flags)
{
	char *p, *q;
	size_t namelen;
	char *nameeq;
	size_t vallen;
	struct var *vp;

	q = endofname(name);
	p = strchrnul(q, '=');
	namelen = p - name;
	if (!namelen || p != q)
		sh_error("%.*s: bad variable name", namelen, name);
	vallen = 0;
	if (val == NULL) {
		flags |= VUNSET;
	} else {
		vallen = strlen(val);
	}
	INTOFF;
	p = mempcpy(nameeq = ckmalloc(namelen + vallen + 2), name, namelen);
	if (val) {
		*p++ = '=';
		p = mempcpy(p, val, vallen);
	}
	*p = '\0';
	vp = setvareq(nameeq, flags | VNOSAVE);
	INTON;

	return vp;
}
