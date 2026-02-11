Cudd_ApaPrintMinterm(
  FILE * fp,
  DdManager * dd,
  DdNode * node,
  int  nvars)
{
    int digits;
    int result;
    DdApaNumber count;

    count = Cudd_ApaCountMinterm(dd,node,nvars,&digits);
    if (count == NULL)
	return(0);
    result = Cudd_ApaPrintDecimal(fp,digits,count);
    FREE(count);
    if (fprintf(fp,"\n") == EOF) {
	return(0);
    }
    return(result);

}
