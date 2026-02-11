_err_free (NEOERR *err)
{
  if (err == NULL || err == INTERNAL_ERR)
    return 0;
  if (err->next != NULL)
    _err_free(err->next);
  if (UseFreeList)
  {
    err->next = FreeList;
    FreeList = err;
    err->flags = 0;
    err->desc[0] = '\0';
  }
  else
  {
    free(err);
  }
  return 0;
}
