gfs_output_scalar_histogram_write (GtsObject * o, FILE * fp)
{
  GfsOutputScalarHistogram * output = GFS_OUTPUT_SCALAR_HISTOGRAM (o);

  (* GTS_OBJECT_CLASS (gfs_output_scalar_histogram_class ())->parent_class->write) (o, fp);

  fprintf (fp, " { n = %d", output->n);
  if (output->wf) {
    fputs (" w = ", fp);
    gfs_function_write (output->wf, fp);
  }
  if (output->yf) {
    fputs (" y = ", fp);
    gfs_function_write (output->yf, fp);
  }
  fputs (" }", fp);
}
