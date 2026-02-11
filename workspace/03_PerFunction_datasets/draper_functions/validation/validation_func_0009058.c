edialign_path(edialignCLOSURE *clos,
			   ajint x, ajint i, ajint y, ajint j)
{
    ajint n2;
    ajint k;

    if(x == y)
	return(i <= j);

    n2 = clos->seq[y].aligSetNbr[j];

    if(n2 == 0)
    {
	k = clos->seq[y].predAligSetPos[j];
	if(k > 0)
	    n2 = clos->seq[y].aligSetNbr[k];
    }

    if(n2 == 0)
	return(0);

    return(i <= clos->predFrontier[n2][x]);
}
