gtr_msg_get_filename (GtrMsg * msg, gint i)
{
  g_return_val_if_fail (GTR_IS_MSG (msg), NULL);

  po_filepos_t filepos;

  filepos = po_message_filepos (msg->priv->message, i);

  if (filepos == NULL)
    return NULL;

  return po_filepos_file (filepos);
}
