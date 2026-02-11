isConnected(Agraph_t * g)
{
    Agnode_t *n;
    int ret = 1;
    int cnt = 0;
    stk_t stk;
    blk_t blk;
    Agnode_t* base[INITBUF];

    for (n = agfstnode(g); n; n = agnxtnode(g, n))
	UNMARK(n);

    n = agfstnode(g);
    if (n) {
	initStk (&stk, &blk, base);
	if (setjmp(jbuf)) {
	    freeStk (&stk);
	    return -1;
        }
	dfs(g, n, cntFn, &cnt, &stk);
	if (cnt != agnnodes(g))
	    ret = 0;
	freeStk (&stk);
    }
    return ret;
}
