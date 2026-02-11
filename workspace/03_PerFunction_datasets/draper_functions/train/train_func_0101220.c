glp_set_col_stat(glp_prob *lp, int j, int stat)
{     GLPCOL *col;
      if (!(1 <= j && j <= lp->n))
         xerror("glp_set_col_stat: j = %d; column number out of range\n"
            , j);
      if (!(stat == GLP_BS || stat == GLP_NL || stat == GLP_NU ||
            stat == GLP_NF || stat == GLP_NS))
         xerror("glp_set_col_stat: j = %d; stat = %d; invalid status\n",
            j, stat);
      col = lp->col[j];
      if (stat != GLP_BS)
      {  switch (col->type)
         {  case GLP_FR: stat = GLP_NF; break;
            case GLP_LO: stat = GLP_NL; break;
            case GLP_UP: stat = GLP_NU; break;
            case GLP_DB: if (stat != GLP_NU) stat = GLP_NL; break;
            case GLP_FX: stat = GLP_NS; break;
            default: xassert(col != col);
         }
      }
      if (col->stat == GLP_BS && stat != GLP_BS ||
          col->stat != GLP_BS && stat == GLP_BS)
      {
         lp->valid = 0;
      }
      col->stat = stat;
      return;
}
