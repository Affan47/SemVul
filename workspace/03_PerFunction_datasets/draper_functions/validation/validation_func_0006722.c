get_bidchan_val(struct chanrec_t *chanp, register struct net_t *np,
 int32 ibi, int32 bi)
{
 register int32 val, chtyp;
 word32 nav, nbv;

 if ((chtyp = chanp->chtyp) == TRPROC_STBID) val = np->nva.bp[ibi + bi];
 else if (chtyp == TRPROC_BID)
  {

   if (!np->n_isavec) ld_scalval_(&nav, &nbv, np->nva.bp);
   else __ld_bit(&nav, &nbv, np, bi);
   val = nav | (nbv << 1);
  }
 else { val = 3; __case_terr(__FILE__, __LINE__); }
 return(val);
}
