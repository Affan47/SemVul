check_existing_goa_accounts (AddAccountData *data)
{
  GList *goa_accounts = NULL;
  GList *l = NULL;
  gboolean found = FALSE;

  if (data->tp_account == NULL || data->goa_client == NULL)
    return FALSE;

  goa_accounts = goa_client_get_accounts (data->goa_client);
  for (l = goa_accounts; l != NULL; l = l->next)
    {
      if (check_goa_object_match (data, l->data))
        {
          found = TRUE;
          break;
        }
    }
  g_list_free_full (goa_accounts, g_object_unref);

  return found;
}
