fil_lin_toscope(int32 ifi, int32 lini, struct itree_t **in_itp,
 struct task_t **in_tskp)
{
 register struct mod_t *mdp;
 register struct task_t *tskp;
 struct mod_t *in_mdp;


 for (in_mdp = NULL, mdp = __modhdr; mdp != NULL; mdp = mdp->mnxt)
  {
   if (scope_lini_inrng(lini, ifi, mdp->msym->sylin_cnt,
    (int32) mdp->msym->syfnam_ind, mdp->mod_last_lini, mdp->mod_last_ifi))
    {
     in_mdp = mdp;
     break;
    }
  }
 if (in_mdp == NULL) return(FALSE);
 *in_itp = in_mdp->moditps[0];


 *in_tskp = NULL;
 for (tskp = mdp->mtasks; tskp != NULL; tskp = tskp->tsknxt)
  {

   if (scope_lini_inrng(lini, ifi, tskp->tsksyp->sylin_cnt,
    (int32) tskp->tsksyp->syfnam_ind, tskp->tsk_last_lini, tskp->tsk_last_ifi))
    { *in_tskp = tskp; break; }
  }
 return(TRUE);
}
