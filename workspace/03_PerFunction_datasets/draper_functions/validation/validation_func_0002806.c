set_aux_bnds(struct csa *csa)
{     int m = csa->m;
      int n = csa->n;
      char *type = csa->type;
      double *lb = csa->lb;
      double *ub = csa->ub;
      char *orig_type = csa->orig_type;
      int *head = csa->head;
      char *stat = csa->stat;
      double *cbar = csa->cbar;
      int j, k;
      for (k = 1; k <= m+n; k++)
      {  switch (orig_type[k])
         {  case GLP_FR:
#if 0
               type[k] = GLP_DB, lb[k] = -1.0, ub[k] = +1.0;
#else

               type[k] = GLP_DB, lb[k] = -1e3, ub[k] = +1e3;
#endif
               break;
            case GLP_LO:
               type[k] = GLP_DB, lb[k] = 0.0, ub[k] = +1.0;
               break;
            case GLP_UP:
               type[k] = GLP_DB, lb[k] = -1.0, ub[k] = 0.0;
               break;
            case GLP_DB:
            case GLP_FX:
               type[k] = GLP_FX, lb[k] = ub[k] = 0.0;
               break;
            default:
               xassert(orig_type != orig_type);
         }
      }
      for (j = 1; j <= n; j++)
      {  k = head[m+j];
#ifdef GLP_DEBUG
         xassert(1 <= k && k <= m+n);
#endif
         if (type[k] == GLP_FX)
            stat[j] = GLP_NS;
         else if (cbar[j] >= 0.0)
            stat[j] = GLP_NL;
         else
            stat[j] = GLP_NU;
      }
      return;
}
