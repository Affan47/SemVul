glp_set_rii(glp_prob *lp, int i, double rii)
{     if (!(1 <= i && i <= lp->m))
         xerror("glp_set_rii: i = %d; row number out of range\n", i);
      if (rii <= 0.0)
         xerror("glp_set_rii: i = %d; rii = %g; invalid scale factor\n",
            i, rii);
      if (lp->valid && lp->row[i]->rii != rii)
      {  GLPAIJ *aij;
         for (aij = lp->row[i]->ptr; aij != NULL; aij = aij->r_next)
         {  if (aij->col->stat == GLP_BS)
            {
               lp->valid = 0;
               break;
            }
         }
      }
      lp->row[i]->rii = rii;
      return;
}
