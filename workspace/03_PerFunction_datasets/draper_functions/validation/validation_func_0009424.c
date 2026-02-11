struct_eq(chainp s1, chainp s2)
#endif
{
    struct Dimblock *d1, *d2;
    Constp cp1, cp2;

    if (s1 == CHNULL && s2 == CHNULL)
	return YES;
    for(; s1 && s2; s1 = s1->nextp, s2 = s2->nextp) {
	register Namep v1 = (Namep) s1 -> datap;
	register Namep v2 = (Namep) s2 -> datap;

	if (v1 == (Namep) NULL || v1 -> tag != TNAME ||
		v2 == (Namep) NULL || v2 -> tag != TNAME)
	    return NO;

	if (v1->vtype != v2->vtype || v1->vclass != v2->vclass
		|| strcmp(v1->fvarname, v2->fvarname))
	    return NO;


	if (d1 = v1->vdim) {
		if (!(cp1 = (Constp)d1->nelt) || cp1->tag != TCONST
		||  !(d2 = v2->vdim)
		||  !(cp2 = (Constp)d2->nelt) || cp2->tag != TCONST
		||  cp1->Const.ci != cp2->Const.ci)
			return NO;
		}
	else if (v2->vdim)
		return NO;
    }

    return s1 == CHNULL && s2 == CHNULL;
}
