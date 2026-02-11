summary_graph(ESL_GETOPTS *go, FILE *fp, struct oneplot_s *plot, double **yv)
{
  int    nboots              = esl_opt_GetInteger(go, "-N");
  int    by_stddev           = esl_opt_GetBoolean(go, "-s");
  double confidence_interval = esl_opt_GetReal   (go, "--interval");
  double nsd                 = esl_opt_GetReal   (go, "--nsd");
  int    xi;
  double false_pos;
  double mean, var;
  int    ntail;

  for (xi = 0; xi < plot->nxpts; xi++)
    {
      false_pos = exp(log(10) * ((double) plot->base + (double) xi) / (double) plot->nsteps);
      esl_stats_DMean(yv[xi], nboots, &mean, &var);


      if (by_stddev)
	{
	  fprintf(fp, "%.5f %.5f %.5f %.5f\n", false_pos, mean, nsd*sqrt(var), nsd*sqrt(var));
	}
      else
	{
	  esl_vec_DSortIncreasing(yv[xi], nboots);
	  ntail = (int) ((double) nboots * (1.0 - confidence_interval) / 2.0);

	  fprintf(fp, "%.5f %.5f %.5f %.5f\n",
		  false_pos, mean,
		  yv[xi][nboots-ntail] - mean,
		  mean - yv[xi][ntail]);
	}
    }
  fprintf(fp, "&\n");
}
