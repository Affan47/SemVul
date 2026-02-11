ds_getc(Ds *ds, FILE *fp, int *ch_ptr)
{
  int ch;

  ds_errmsg = NULL;
  if (ds->len_limit > 0 && ds->len == ds->len_limit) {
	ds_errmsg = "max limit exceeded";
	return(-2);
  }

  if ((ch = getc(fp)) == EOF) {
	if (feof(fp))
	  return(0);
	if (ferror(fp))
	  return(-1);
  }

  if (ds_appendc(ds, ch) == -1)
	return(-1);

  if (ch_ptr != NULL)
	*ch_ptr = ch;

  return(1);
}
