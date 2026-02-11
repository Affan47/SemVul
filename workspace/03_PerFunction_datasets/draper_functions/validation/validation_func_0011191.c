gfs_function_write (GfsFunction * f, FILE * fp)
{
  g_return_if_fail (f != NULL);
  g_return_if_fail (fp != NULL);

  (* GTS_OBJECT (f)->klass->write) (GTS_OBJECT (f), fp);
}
