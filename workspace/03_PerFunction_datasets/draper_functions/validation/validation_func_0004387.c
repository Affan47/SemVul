prep_sdfiopath_verbmsg(struct spcpth_t *pthp, struct gate_t *ogp,
 struct itree_t *itp, struct mod_t *mdp)
{
 register int32 ii;
 register struct itree_t *itp2;
 char s1[RECLEN], s2[RECLEN];

 if (itp == NULL)
  {
   for (ii = 0; ii < mdp->flatinum; ii++)
    {
     itp2 = mdp->moditps[ii];
     __push_itstk(itp2);
     sprintf(s1, "%s(%s) from '*'", __msg2_blditree(s2, itp2),
      mdp->msym->synam);
     emit_sdfiopath_verbmsg(pthp, ogp, s1);
     __pop_itstk();
    }
  }
 else
  {
   __push_itstk(itp);
   sprintf(s1, "%s(%s)", __msg2_blditree(s2, itp), mdp->msym->synam);
   emit_sdfiopath_verbmsg(pthp, ogp, s1);
   __pop_itstk();
  }
}
