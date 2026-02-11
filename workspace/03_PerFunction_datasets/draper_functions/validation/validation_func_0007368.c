_pstdout_consolidated_data_create(const char *hostname, const char *output)
{
  struct pstdout_consolidated_data *cdata = NULL;

  assert(hostname);
  assert(output);

  if (!(cdata = (struct pstdout_consolidated_data *)malloc(sizeof(struct pstdout_consolidated_data))))
    {
      pstdout_errnum = PSTDOUT_ERR_OUTMEM;
      goto cleanup;
    }
  memset(cdata, '\0', sizeof(struct pstdout_consolidated_data));

  if (!(cdata->h = hostlist_create(hostname)))
    {
      pstdout_errnum = PSTDOUT_ERR_OUTMEM;
      goto cleanup;
    }

  if (!(cdata->output = strdup(output)))
    {
      pstdout_errnum = PSTDOUT_ERR_OUTMEM;
      goto cleanup;
    }

  return cdata;

 cleanup:
  if (cdata)
    {
      if (cdata->h)
        hostlist_destroy(cdata->h);
      free(cdata->output);
      free(cdata);
    }
  return NULL;
}
