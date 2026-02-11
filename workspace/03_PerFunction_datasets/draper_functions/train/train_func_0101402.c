fill_from_language_entry (GtrLanguagesFetcher *fetcher,
                          GtrLanguage         *lang)
{
  const gchar *entry_text;

  fill_encoding_and_charset (fetcher);

  entry_text = gtk_entry_get_text (GTK_ENTRY (gtk_bin_get_child (GTK_BIN (fetcher->priv->language_code))));

  if (*entry_text == '\0')
    {
      const gchar *code;

      code = gtr_language_get_code (lang);

      if (code != NULL && *code != '\0')
        gtk_entry_set_text (GTK_ENTRY (gtk_bin_get_child (GTK_BIN (fetcher->priv->language_code))), code);
    }

  entry_text = gtk_entry_get_text (GTK_ENTRY (gtk_bin_get_child (GTK_BIN (fetcher->priv->plural_forms))));

  if (*entry_text == '\0')
    {
      const gchar *plural_form;

      plural_form = gtr_language_get_plural_form (lang);

      if (plural_form != NULL && *plural_form != '\0')
        gtk_entry_set_text (GTK_ENTRY (gtk_bin_get_child (GTK_BIN (fetcher->priv->plural_forms))), plural_form);
    }
}
