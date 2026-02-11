facet_vector_integral_q_grad(f_info)
struct qinfo *f_info;
{ int m,i,j,k;
  REAL value = 0.0;
  REAL val;
  REAL derivs[MAXCOORD];
  REAL sign = (get_fattr(f_info->id) & NEGBOUNDARY) ? -1.0 : 1.0;

  for ( k = 0 ; k < FACET_CTRL ; k++ )
     for ( j = 0 ; j < SDIM ; j++ )
        f_info->grad[k][j] = 0.0;

  for ( m = 0 ; m < gauss2D_num ; m++ )
  {
     REAL **gpp = gpolypartial[m];
     REAL wt = sign*0.5*gauss2Dwt[m];
     REAL **tang = f_info->sides[m];
     f_info->gauss_pt[m][2*SDIM] = m;
     for ( j = 0 ; j < SDIM ; j++ )
     { int jj = (j+1)%SDIM;
       int jjj = (j+2)%SDIM;
       eval_all(METH_INSTANCE(f_info->method)->expr[j],f_info->gauss_pt[m],SDIM,&val,
                                                        derivs,f_info->id);
       value += wt*val*(tang[0][jj]*tang[1][jjj] - tang[0][jjj]*tang[1][jj]);

       for ( k = 0 ; k < FACET_CTRL ; k++ )
        {
          f_info->grad[k][jj] += wt*val
                *(gpp[0][k]*tang[1][jjj] - tang[0][jjj]*gpp[1][k]);
          f_info->grad[k][jjj] += wt*val
                *(tang[0][jj]*gpp[1][k] - gpp[0][k]*tang[1][jj]);
          for ( i = 0 ; i < SDIM ; i++ )
             f_info->grad[k][i] += wt*derivs[i]*gpoly[m][k]
                     *(tang[0][jj]*tang[1][jjj] - tang[0][jjj]*tang[1][jj]);
        }
     }
  }

  return value;
}
