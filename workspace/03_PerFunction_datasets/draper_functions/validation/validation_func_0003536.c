setup_1argdvars(struct mdvmast_t *mdvp)
{
 struct net_t *np;
 struct mod_t *mdp;
 struct itree_t *itp;


 if ((np = mdvp->mdv_np) != NULL)
  {

   if (np->n_isarr) return;


   itp = mdvp->mdv_itprt;
   mdp = itp->itip->imsym->el.emdp;
   turnon_1net_dmpv(np, itp, mdvp->mdv_tskp, mdp, FALSE);
  }
 else
  {


   setup_1subtree_allvars(mdvp->mdv_itprt, mdvp->mdv_levels);
  }
}
