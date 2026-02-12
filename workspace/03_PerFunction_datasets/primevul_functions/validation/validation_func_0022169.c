Agraph_t *agroot(void* obj)
{

    if (obj == 0) return NILgraph;
    switch (AGTYPE(obj)) {
    case AGINEDGE:
    case AGOUTEDGE:
	return ((Agedge_t *) obj)->node->root;
    case AGNODE:
	return ((Agnode_t *) obj)->root;
    case AGRAPH:
	return ((Agraph_t *) obj)->root;
    default:
	agerr(AGERR, "agroot of a bad object");
	return NILgraph;
    }
}
