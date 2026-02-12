void imap_free_header_data (IMAP_HEADER_DATA** data)
{
  if (*data)
  {

    mutt_free_list (&((*data)->keywords));
    FREE (data);
  }
}
