static void imap_alloc_msn_index (IMAP_DATA *idata, unsigned int msn_count)
{
  unsigned int new_size;

  if (msn_count <= idata->msn_index_size)
    return;


  if (msn_count >= (UINT_MAX / sizeof (HEADER *)))
  {
    mutt_error _("Integer overflow -- can't allocate memory.");
    sleep (1);
    mutt_exit (1);
  }


  new_size = msn_count + 25;

  if (!idata->msn_index)
    idata->msn_index = safe_calloc (new_size, sizeof (HEADER *));
  else
  {
    safe_realloc (&idata->msn_index, sizeof (HEADER *) * new_size);
    memset (idata->msn_index + idata->msn_index_size, 0,
            sizeof (HEADER *) * (new_size - idata->msn_index_size));
  }

  idata->msn_index_size = new_size;
}
