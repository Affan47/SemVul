gtr_header_get_translator (GtrHeader * header)
{
  gchar *space, *translator_temp, *translator;

  g_return_val_if_fail (GTR_IS_HEADER (header), NULL);

  translator_temp = po_header_field (gtr_msg_get_msgstr (GTR_MSG (header)),
                                     "Last-Translator");
  space = g_strrstr (translator_temp, " <");

  if (!space)
    translator = g_strdup (translator_temp);
  else
    translator = g_strndup (translator_temp, space - translator_temp);

  g_free (translator_temp);

  return translator;
}
