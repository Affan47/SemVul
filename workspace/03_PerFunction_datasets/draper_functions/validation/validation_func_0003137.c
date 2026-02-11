msbdf_update (void *vstate, const size_t dim, gsl_matrix * dfdy, double *dfdt,
              const double t, const double *y, const gsl_odeiv2_system * sys,
              gsl_matrix * M, gsl_permutation * p,
              const size_t iter, size_t * nJ, size_t * nM,
              const double tprev, const double failt,
              const double gamma, const double gammaprev, const double hratio)
{


  const double c = 0.2;
  const double gammarel = fabs (gamma / gammaprev - 1.0);

  if (*nJ == 0 || *nJ > MSBDF_JAC_WAIT ||
      (t == failt && (gammarel < c || hratio < 1.0)))
    {
#ifdef DEBUG
      printf ("-- evaluate jacobian\n");
#endif
      int s = GSL_ODEIV_JA_EVAL (sys, t, y, dfdy->data, dfdt);

      if (s == GSL_EBADFUNC)
        {
          return s;
        }

      if (s != GSL_SUCCESS)
        {
          msbdf_failurehandler (vstate, dim, t);
#ifdef DEBUG
          printf ("-- FAIL at jacobian function evaluation\n");
#endif
          return s;
        }


      *nJ = 0;
    }


  if (*nM == 0 || *nM > MSBDF_M_WAIT || gammarel >= c ||
      t == tprev || t == failt)
    {
#ifdef DEBUG
      printf ("-- update M, gamma=%.5e\n", gamma);
#endif
      size_t i;
      gsl_matrix_memcpy (M, dfdy);
      gsl_matrix_scale (M, -gamma);

      for (i = 0; i < dim; i++)
        {
          gsl_matrix_set (M, i, i, gsl_matrix_get (M, i, i) + 1.0);
        }

      {
        int signum;
        int s = gsl_linalg_LU_decomp (M, p, &signum);

        if (s != GSL_SUCCESS)
          {
            return GSL_FAILURE;
          }
      }


      *nM = 0;
    }

  return GSL_SUCCESS;
}
