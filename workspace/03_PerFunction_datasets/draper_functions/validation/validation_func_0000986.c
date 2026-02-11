fromstring_gmp_fscanf (const char *input, const char *fmt, ...)
{
  va_list  ap;
  FILE     *fp;
  int      ret;
  va_start (ap, fmt);

  fp = fopen (TEMPFILE, "w+");
  ASSERT_ALWAYS (fp != NULL);
  ASSERT_ALWAYS (fputs (input, fp) != EOF);
  ASSERT_ALWAYS (fflush (fp) == 0);
  rewind (fp);

  ret = gmp_vfscanf (fp, fmt, ap);
  got_ftell = ftell (fp);
  ASSERT_ALWAYS (got_ftell != -1L);

  fromstring_next_c = getc (fp);

  ASSERT_ALWAYS (fclose (fp) == 0);
  va_end (ap);
  return ret;
}
