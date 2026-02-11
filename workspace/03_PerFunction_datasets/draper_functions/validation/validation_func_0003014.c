FcLangSetCompareStrSet (const FcLangSet *ls, FcStrSet *set)
{
    FcStrList	    *list = FcStrListCreate (set);
    FcLangResult    r, best = FcLangDifferentLang;
    FcChar8	    *extra;

    if (list)
    {
	while (best > FcLangEqual && (extra = FcStrListNext (list)))
	{
	    r = FcLangSetHasLang (ls, extra);
	    if (r < best)
		best = r;
	}
	FcStrListDone (list);
    }
    return best;
}
