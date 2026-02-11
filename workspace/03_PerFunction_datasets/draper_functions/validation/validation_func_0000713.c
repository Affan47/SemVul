failFree(pat)
Cell pat; {
    Cell c = getHead(pat);

    switch (whatIs(c)) {
	case ASPAT     : return failFree(snd(snd(pat)));

	case NAME      : if (!isCfun(c) || cfunOf(c)!=0)
			     return FALSE;

	case TUPLE     : for (; isAp(pat); pat=fun(pat))
			     if (!failFree(arg(pat)))
				return FALSE;

	case LAZYPAT   :
	case VAROPCELL :
	case VARIDCELL :
	case DICTVAR   :
	case WILDCARD  : return TRUE;

#if TREX
	case EXT       : return failFree(extField(pat)) &&
				failFree(extRow(pat));
#endif

	case CONFLDS   : if (cfunOf(fst(snd(c)))==0) {
			     List fs = snd(snd(c));
			     for (; nonNull(fs); fs=tl(fs))
				 if (!failFree(snd(hd(fs))))
				     return FALSE;
			     return TRUE;
			 }

	default        : return FALSE;
    }
}
