compare_edges_by_zmin(SORTFUNC_ARGS p1, SORTFUNC_ARGS p2)
{
    return SIGN(vlist[elist[*(const long *) p1].v2].z
		- vlist[elist[*(const long *) p2].v2].z);
}
