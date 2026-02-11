_cdio_strfreev(char **strv)
{
  int n;

  cdio_assert (strv != NULL);

  for(n = 0; strv[n]; n++)
    free(strv[n]);

  free(strv);
}
