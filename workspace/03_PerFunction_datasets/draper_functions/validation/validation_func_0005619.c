ftvar_clear(struct ftvar *ftvar, char *name)
{
  struct ftvar_entry *ftve;

  if ((ftve = ftvar_find(ftvar, name))) {

    if (ftve->name)
      free(ftve->name);

    if (ftve->val)
      free(ftve->val);

    FT_SLIST_REMOVE(&ftvar->entries, ftve, ftvar_entry, chain);

    free(ftve);

  }

}
