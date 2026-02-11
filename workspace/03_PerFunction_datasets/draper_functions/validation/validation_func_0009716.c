gtr_translation_memory_populate (GtrPopulateData *data)
{
  GtrMsg *msg;

  if (!data->messages)
    return FALSE;

  msg = (GtrMsg *)data->messages->data;
  store_message (data->activatable, msg);
  data->messages = g_list_next (data->messages);

  return TRUE;
}
