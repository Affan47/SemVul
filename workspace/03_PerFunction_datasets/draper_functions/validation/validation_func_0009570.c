gfs_domain_depth (GfsDomain * domain)
{
  guint depth = 0;

  g_return_val_if_fail (domain != NULL, 0);

  gts_container_foreach (GTS_CONTAINER (domain),
			 (GtsFunc) box_depth, &depth);
  gfs_all_reduce (domain, depth, MPI_UNSIGNED, MPI_MAX);
  return depth;
}
