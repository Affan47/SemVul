pkvec_resize (pkvec_struct *pkvec, int sze)


{ pkcoeff_struct *coeffs ;

  const char *rtnnme = "pkvec_resize" ;

# ifdef DYLP_PARANOIA
  if (pkvec == NULL)
  { errmsg(2,rtnnme,"pkvec") ;
    return (FALSE) ; }
  if ((pkvec->coeffs == NULL && (pkvec->sze > 0 || pkvec->cnt > 0)) ||
      (pkvec->cnt > pkvec->sze))
  { errmsg(90,rtnnme,(pkvec->nme == NULL)?"<<null>>":pkvec->nme,
	   pkvec->ndx,pkvec->sze,pkvec->cnt,(pkvec->coeffs == NULL)?"un":"") ;
    return (FALSE) ; }
#endif

  if (sze == 0) sze = minn((int)(pkvec->sze*1.1),pkvec->sze+10) ;
  if (sze < pkvec->cnt)
  { errmsg(91,rtnnme,(pkvec->nme == NULL)?"<<null>>":pkvec->nme,
	   pkvec->ndx,pkvec->cnt,sze) ;
    return (FALSE) ; }

  coeffs = pkvec->coeffs ;
  pkvec->coeffs =
      (pkcoeff_struct *) REALLOC(pkvec->coeffs,sizeof(pkcoeff_struct)*sze) ;
  if (pkvec->coeffs == NULL)
  { errmsg(8,rtnnme,__LINE__,sizeof(pkcoeff_struct)*sze) ;
    pkvec->coeffs = coeffs ;
    return (FALSE) ; }
  pkvec->sze = sze ;

  return (TRUE) ; }
