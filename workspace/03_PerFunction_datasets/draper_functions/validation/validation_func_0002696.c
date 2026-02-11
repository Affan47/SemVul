_Xrealpath(path, plen, resolved, tlen, rlen, flags)
CONST char *path;
int plen;
char *resolved;
int tlen, rlen, flags;
{
#ifndef	NOSYMLINK
	int n;
#endif
	char *cp, *top;
	int len;

	if (plen <= 0) return(rlen);
	else if (path[0] != '.') ;
	else if (plen == 1) return(rlen);
	else if (path[1] != '.') ;
	else if (plen == 2) {
		top = &(resolved[tlen]);
		cp = strrdelim(top, 0);
		if (!cp || cp <= top) {
			copyrootpath(top);
			return(++tlen);
		}
		*cp = '\0';
		return(cp - top);
	}

	if ((cp = Xmemchr(path, _SC_, plen))) {
		len = cp++ - path;
		rlen = _Xrealpath(path, len, resolved, tlen, rlen, flags);
		plen -= ++len;
		return(_Xrealpath(cp, plen, resolved, tlen, rlen, flags));
	}

	len = Xsnprintf(&(resolved[rlen]), MAXPATHLEN - rlen,
		"%s%-.*s", (rlen > tlen + 1) ? _SS_ : nullstr, plen, path);
#ifdef	CODEEUC
	len = strlen(&(resolved[rlen]));
#endif
#ifndef	NOSYMLINK
	if ((flags & RLP_READLINK)
	&& (n = evallink(resolved, tlen, rlen)) > 0) {
		rlen = n;
		len = 0;
	}
#endif
	rlen += len;

	return(rlen);
}
