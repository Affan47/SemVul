startCudd(
  NtrOptions * option,
  int  nvars)
{
    DdManager *dd;
    int result;

    dd = Cudd_Init(0, 0, option->slots, option->cacheSize, option->maxMemory);
    if (dd == NULL) return(NULL);

    if (option->maxMemHard != 0) {
	Cudd_SetMaxMemory(dd,option->maxMemHard);
    }
    Cudd_SetMaxLive(dd,option->maxLive);
    Cudd_SetGroupcheck(dd,option->groupcheck);
    if (option->autoDyn & 1) {
	Cudd_AutodynEnable(dd,option->autoMethod);
    }
    dd->nextDyn = option->firstReorder;
    dd->countDead = (option->countDead == FALSE) ? ~0 : 0;
    dd->maxGrowth = 1.0 + ((float) option->maxGrowth / 100.0);
    dd->recomb = option->recomb;
    dd->arcviolation = option->arcviolation;
    dd->symmviolation = option->symmviolation;
    dd->populationSize = option->populationSize;
    dd->numberXovers = option->numberXovers;
    result = ntrReadTree(dd,option->treefile,nvars);
    if (result == 0) {
	Cudd_Quit(dd);
	return(NULL);
    }
#ifndef DD_STATS
    result = Cudd_EnableReorderingReporting(dd);
    if (result == 0) {
	(void) fprintf(stderr,
		       "Error reported by Cudd_EnableReorderingReporting\n");
	Cudd_Quit(dd);
	return(NULL);
    }
#endif

    return(dd);

}
