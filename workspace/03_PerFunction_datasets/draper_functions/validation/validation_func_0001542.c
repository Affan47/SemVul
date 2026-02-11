gfs_output_scalar_maxima_destroy (GtsObject * o)
{
  guint i;

  for (i = 0; i < 4; i++)
    g_free (GFS_OUTPUT_SCALAR_MAXIMA (o)->m[i]);

  (* GTS_OBJECT_CLASS (gfs_output_scalar_maxima_class ())->parent_class->destroy) (o);
}
