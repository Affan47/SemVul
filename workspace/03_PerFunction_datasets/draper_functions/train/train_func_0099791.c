edgeLen (Agedge_t* e)
{
    pointf p = ND_coord(agtail(e));
    pointf q = ND_coord(aghead(e));
    return (int)DIST2(p,q);
}
