xmlXPathNodeSetSort(xmlNodeSetPtr set) {
#ifndef WITH_TIM_SORT
    int i, j, incr, len;
    xmlNodePtr tmp;
#endif

    if (set == NULL)
	return;

#ifndef WITH_TIM_SORT


    len = set->nodeNr;
    for (incr = len / 2; incr > 0; incr /= 2) {
	for (i = incr; i < len; i++) {
	    j = i - incr;
	    while (j >= 0) {
#ifdef XP_OPTIMIZED_NON_ELEM_COMPARISON
		if (xmlXPathCmpNodesExt(set->nodeTab[j],
			set->nodeTab[j + incr]) == -1)
#else
		if (xmlXPathCmpNodes(set->nodeTab[j],
			set->nodeTab[j + incr]) == -1)
#endif
		{
		    tmp = set->nodeTab[j];
		    set->nodeTab[j] = set->nodeTab[j + incr];
		    set->nodeTab[j + incr] = tmp;
		    j -= incr;
		} else
		    break;
	    }
	}
    }
#else
    libxml_domnode_tim_sort(set->nodeTab, set->nodeNr);
#endif
}
