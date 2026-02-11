openG(char *name, Agdesc_t desc)
{
    Agraph_t *g;

#ifdef WIN32
    gprDisc.mem = &AgMemDisc;
    gprDisc.id = &AgIdDisc;
#endif
    g = agopen(name, desc, &gprDisc);
    if (g)
	agbindrec(g, UDATA, sizeof(gdata), 0);
    return g;
}
