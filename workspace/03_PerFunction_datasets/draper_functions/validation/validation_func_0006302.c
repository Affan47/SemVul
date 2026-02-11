__copy_dellst(struct paramlst_t *oplp)
{
 register struct paramlst_t *plp;
 struct paramlst_t *nplphdr, *nplp, *last_nplp;

 if (oplp == NULL) return(NULL);

 nplphdr = NULL;
 for (last_nplp = NULL, plp = oplp; plp != NULL; plp = plp->pmlnxt)
  {
   nplp = __alloc_pval();
   nplp->plxndp = __copy_expr(plp->plxndp);
   if (last_nplp == NULL) nplphdr = nplp; else last_nplp->pmlnxt = nplp;
   nplp->pmlnxt = NULL;
   last_nplp = nplp;
  }
 return(nplphdr);
}
