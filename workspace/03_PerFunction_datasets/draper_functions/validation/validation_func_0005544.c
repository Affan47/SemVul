stream_from_vorticity (GfsDomain * domain,
				   GfsVariable * stream,
				   GfsVariable * vorticity,
				   gdouble tolerance)
{
  GfsNorm norm;
  guint maxit = 100;
  GfsVariable * res, * dia;
  GfsMultilevelParams par;

  g_return_if_fail (domain != NULL);

  dia = gfs_temporary_variable (domain);
  gfs_poisson_coefficients (domain, NULL, TRUE, TRUE);
  gfs_domain_cell_traverse (domain, FTT_PRE_ORDER, FTT_TRAVERSE_ALL, -1,
			    (FttCellTraverseFunc) gfs_cell_reset, dia);
  correct_div (domain, vorticity);
  gfs_domain_cell_traverse (domain, FTT_PRE_ORDER, FTT_TRAVERSE_LEAFS, -1,
			    (FttCellTraverseFunc) gfs_cell_reset, stream);
  res = gfs_temporary_variable (domain);
  gfs_residual (domain, FTT_DIMENSION, FTT_TRAVERSE_LEAFS, -1, stream, vorticity, dia, res);
  norm = gfs_domain_norm_residual (domain, FTT_TRAVERSE_LEAFS, -1, 1., res);
  gfs_multilevel_params_init (&par);
  par.depth = gfs_domain_depth (domain);
  while (norm.infty > tolerance && maxit) {
    gfs_poisson_cycle (domain, &par, stream, vorticity, dia, res);
    norm = gfs_domain_norm_residual (domain, FTT_TRAVERSE_LEAFS, -1, 1., res);
    maxit--;
  }
  if (maxit == 0)
    g_warning ("GfsInitVorticity: cannot solve streamfunction from vorticity\n"
	       "  (residual: %g)", norm.infty);
  gts_object_destroy (GTS_OBJECT (res));
  gts_object_destroy (GTS_OBJECT (dia));
}
