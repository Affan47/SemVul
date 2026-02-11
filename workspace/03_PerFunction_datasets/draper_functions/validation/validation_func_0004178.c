stab_typdef (void *p, const char *name)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  long tindex;
  unsigned int size;
  char *s, *buf;
  struct string_hash_entry *h;

  tindex = info->type_stack->index;
  size = info->type_stack->size;
  s = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (name) + strlen (s) + 20);

  if (tindex > 0)
    sprintf (buf, "%s:t%s", name, s);
  else
    {
      tindex = info->type_index;
      ++info->type_index;
      sprintf (buf, "%s:t%ld=%s", name, tindex, s);
    }

  free (s);

  if (! stab_write_symbol (info, N_LSYM, 0, 0, buf))
    return FALSE;

  free (buf);

  h = string_hash_lookup (&info->typedef_hash, name, TRUE, FALSE);
  if (h == NULL)
    {
      non_fatal (_("string_hash_lookup failed: %s"),
		 bfd_errmsg (bfd_get_error ()));
      return FALSE;
    }


  h->index = tindex;
  h->size = size;

  return TRUE;
}
