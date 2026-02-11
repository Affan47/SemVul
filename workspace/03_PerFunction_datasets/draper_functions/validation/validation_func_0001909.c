FcPatternObjectFindElt (const FcPattern *p, FcObject object)
{
    int	    i = FcPatternObjectPosition (p, object);
    if (i < 0)
	return 0;
    return &FcPatternElts(p)[i];
}
