gfs_interpolate (FttCell * cell,
			 FttVector p,
			 GfsVariable * v)
{
  g_return_val_if_fail (cell != NULL, 0.);
  g_return_val_if_fail (v != NULL, 0.);

  if (GFS_VALUE (cell, v) == GFS_NODATA)
    return GFS_NODATA;

  gdouble f[4*(FTT_DIMENSION - 1)];
  gfs_cell_corner_values (cell, v, -1, f);
  return gfs_interpolate_from_corners (cell, p, f);
}
