Cudd_addTimesPlus(
  DdManager * dd,
  DdNode * A,
  DdNode * B,
  DdNode ** z,
  int  nz)
{
    DdNode *w, *cube, *tmp, *res;
    int i;
    tmp = Cudd_addApply(dd,Cudd_addTimes,A,B);
    if (tmp == NULL) return(NULL);
    Cudd_Ref(tmp);
    Cudd_Ref(cube = DD_ONE(dd));
    for (i = nz-1; i >= 0; i--) {
	 w = Cudd_addIte(dd,z[i],cube,DD_ZERO(dd));
	 if (w == NULL) {
	    Cudd_RecursiveDeref(dd,tmp);
	    return(NULL);
	 }
	 Cudd_Ref(w);
	 Cudd_RecursiveDeref(dd,cube);
	 cube = w;
    }
    res = Cudd_addExistAbstract(dd,tmp,cube);
    if (res == NULL) {
	Cudd_RecursiveDeref(dd,tmp);
	Cudd_RecursiveDeref(dd,cube);
	return(NULL);
    }
    Cudd_Ref(res);
    Cudd_RecursiveDeref(dd,cube);
    Cudd_RecursiveDeref(dd,tmp);
    Cudd_Deref(res);
    return(res);

}
