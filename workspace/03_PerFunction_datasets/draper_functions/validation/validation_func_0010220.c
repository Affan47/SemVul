inf_text_gtk_buffer_record_check(InfTextGtkBuffer* buffer,
                                 InfTextGtkBufferRecord* record)
{
  InfTextGtkBufferPrivate* priv;
  InfTextChunk* chunk;
  guint text_len;
  guint buf_len;
  gpointer buf_text;
  gpointer chunk_text;
  gsize buf_bytes;
  gsize chunk_bytes;
  int result;

  priv = INF_TEXT_GTK_BUFFER_PRIVATE(buffer);

  text_len = inf_text_chunk_get_length(record->chunk);
  buf_len = gtk_text_buffer_get_char_count(priv->buffer);


  if(record->insert)
  {
    if(record->char_count + text_len != buf_len)
      return FALSE;
    if(record->position + text_len > buf_len)
      return FALSE;

    chunk = inf_text_buffer_get_slice(
      INF_TEXT_BUFFER(buffer),
      record->position,
      text_len
    );

    buf_text = inf_text_chunk_get_text(record->chunk, &buf_bytes);
    chunk_text = inf_text_chunk_get_text(chunk, &chunk_bytes);
    inf_text_chunk_free(chunk);

    if(buf_bytes == chunk_bytes)
      result = memcmp(buf_text, chunk_text, buf_bytes);
    else
      result = -1;

    g_free(buf_text);
    g_free(chunk_text);

    if(result != 0) return FALSE;
  }
  else
  {
    if(text_len > record->char_count)
      return FALSE;
    if(record->char_count - text_len != buf_len)
      return FALSE;
  }

  return TRUE;
}
