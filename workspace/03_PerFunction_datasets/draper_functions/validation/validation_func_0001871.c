p7_GNull2_ByExpectation(const P7_PROFILE *gm, P7_GMX *pp, float *null2)
{
  int      M      = gm->M;
  int      Ld     = pp->L;
  float  **dp     = pp->dp;
  float   *xmx    = pp->xmx;
  float    xfactor;
  int      x;
  int      i;
  int      k;


  esl_vec_FCopy(pp->dp[1],            (M+1)*p7G_NSCELLS, pp->dp[0]);
  esl_vec_FCopy(pp->xmx+p7G_NXCELLS,  p7G_NXCELLS,       pp->xmx);
  for (i = 2; i <= Ld; i++)
    {
      esl_vec_FAdd(pp->dp[0], pp->dp[i],             (M+1)*p7G_NSCELLS);
      esl_vec_FAdd(pp->xmx,   pp->xmx+i*p7G_NXCELLS, p7G_NXCELLS);
    }


  esl_vec_FLog(pp->dp[0], (M+1)*p7G_NSCELLS);
  esl_vec_FLog(pp->xmx,   p7G_NXCELLS);

  esl_vec_FIncrement(pp->dp[0], (M+1)*p7G_NSCELLS, -log((float)Ld));
  esl_vec_FIncrement(pp->xmx,   p7G_NXCELLS,       -log((float)Ld));


  xfactor = XMX(0,p7G_N);
  xfactor = p7_FLogsum(xfactor, XMX(0,p7G_C));
  xfactor = p7_FLogsum(xfactor, XMX(0,p7G_J));
  esl_vec_FSet(null2, gm->abc->K, -eslINFINITY);
  for (x = 0; x < gm->abc->K; x++)
    {
      for (k = 1; k < M; k++)
	{
	  null2[x] = p7_FLogsum(null2[x], MMX(0,k) + p7P_MSC(gm, k, x));
	  null2[x] = p7_FLogsum(null2[x], IMX(0,k) + p7P_ISC(gm, k, x));
	}
      null2[x] = p7_FLogsum(null2[x], MMX(0,M) + p7P_MSC(gm, k, x));
      null2[x] = p7_FLogsum(null2[x], xfactor);
    }

  esl_vec_FExp (null2, gm->abc->K);


  esl_abc_FAvgScVec(gm->abc, null2);
  null2[gm->abc->K]    = 1.0;
  null2[gm->abc->Kp-2] = 1.0;
  null2[gm->abc->Kp-1] = 1.0;

  return eslOK;
}
