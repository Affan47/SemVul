embedded_key_validation(const struct affine_point *p,
			    const struct domain_params *dp)
{
  if (gcry_mpi_cmp_ui(p->x, 0) < 0 || gcry_mpi_cmp(p->x, dp->m) >= 0 ||
      gcry_mpi_cmp_ui(p->y, 0) < 0 || gcry_mpi_cmp(p->y, dp->m) >= 0)
    return 0;
  return ! point_is_zero(p) && point_on_curve(p, dp);
}
