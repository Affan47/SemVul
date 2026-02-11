StoreCnfNodeByNodeRecur (
  DdManager *ddMgr   ,
  DdNode *f          ,
  int *bddIds        ,
  int *cnfIds        ,
  FILE *fp           ,
  int *clauseN      ,
  int *varMax
  )
{
  DdNode *T, *E;
  int idf, idT, idE, vf;
  int retValue;

#ifdef DDDMP_DEBUG
  assert(!Cudd_IsComplement(f));
  assert(f!=NULL);
#endif


  if (Cudd_IsConstant(f)) {
    return (1);
  }


  if (DddmpVisitedCnf (f)) {
    return (1);
  }


  DddmpSetVisitedCnf (f);


#ifdef DDDMP_DEBUG

  assert (!cuddIsConstant(f));
#endif


  T = cuddT (f);
#ifdef DDDMP_DEBUG

  assert (!Cudd_IsComplement(T));
#endif

  retValue = StoreCnfNodeByNodeRecur (ddMgr, T, bddIds, cnfIds, fp,
    clauseN, varMax);
  if (retValue != 1) {
    return(retValue);
  }


  E = Cudd_Regular (cuddE (f));
  retValue = StoreCnfNodeByNodeRecur (ddMgr, E, bddIds, cnfIds, fp,
    clauseN, varMax);
  if (retValue != 1) {
    return (retValue);
  }


  idf = DddmpReadNodeIndexCnf (f);
  vf = f->index;

  if (bddIds[vf] != vf) {
    (void) fprintf (stderr, "DdStoreCnf: Error writing to file\n");
    fflush (stderr);
    return (0);
  }

  idT = DddmpReadNodeIndexCnf (T);

  idE = DddmpReadNodeIndexCnf (E);
  if (Cudd_IsComplement (cuddE (f))) {
    idE = -idE;
  }

  retValue = StoreCnfOneNode (f, idf, cnfIds[vf], idT, idE, fp,
   clauseN, varMax);

  if (retValue == EOF) {
    return (0);
  } else {
    return (1);
  }
}
