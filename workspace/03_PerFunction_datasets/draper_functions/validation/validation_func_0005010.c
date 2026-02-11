findList (int lindex, GLdouble *paramArray, int size)
{
    MODELPTR endList;
    int found = 0;

    endList = lists[lindex];
    while (endList != NULL) {
	if (compareParams (endList->params, paramArray, size))
	    return (endList->list);
	endList = endList->ptr;
    }


    return (0);
}
