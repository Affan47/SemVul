CreateBotDist(
  DdNode * node,
  st_table * distanceTable)
{
    DdNode *N, *Nv, *Nnv;
    int distance, distanceNv, distanceNnv;
    NodeStat *nodeStat, *nodeStatNv, *nodeStatNnv;

#if 0
    if (Cudd_IsConstant(node)) {
	return(0);
    }
#endif


    N = Cudd_Regular(node);
    if (st_lookup(distanceTable, N, &nodeStat)) {
	nodeStat->localRef++;
	return(nodeStat);
    }

    Nv = cuddT(N);
    Nnv = cuddE(N);
    Nv = Cudd_NotCond(Nv, Cudd_IsComplement(node));
    Nnv = Cudd_NotCond(Nnv, Cudd_IsComplement(node));


    nodeStatNv = CreateBotDist(Nv, distanceTable);
    if (nodeStatNv == NULL) return(NULL);
    distanceNv = nodeStatNv->distance;

    nodeStatNnv = CreateBotDist(Nnv, distanceTable);
    if (nodeStatNnv == NULL) return(NULL);
    distanceNnv = nodeStatNnv->distance;


    distance = (distanceNv > distanceNnv) ? (distanceNv+1) : (distanceNnv + 1);

    nodeStat = ALLOC(NodeStat, 1);
    if (nodeStat == NULL) {
	return(0);
    }
    nodeStat->distance = distance;
    nodeStat->localRef = 1;

    if (st_insert(distanceTable, (char *)N, (char *)nodeStat) ==
	ST_OUT_OF_MEM) {
	return(0);

    }
    return(nodeStat);

}
