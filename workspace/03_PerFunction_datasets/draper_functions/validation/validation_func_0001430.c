set_buffer (GtkSpellChecker *spell, GtkTextBuffer *buffer)
{
  GtkTextIter start, end;

  if (spell->priv->buffer)
    {
      g_signal_handlers_disconnect_matched (spell->priv->buffer, G_SIGNAL_MATCH_DATA,
                                            0, 0, NULL, NULL, spell);

      gtk_text_buffer_get_bounds (spell->priv->buffer, &start, &end);
      gtk_text_buffer_remove_tag (spell->priv->buffer, spell->priv->tag_highlight,
                                  &start, &end);
      spell->priv->tag_highlight = NULL;

      gtk_text_buffer_delete_mark (spell->priv->buffer, spell->priv->mark_insert_start);
      spell->priv->mark_insert_start = NULL;
      gtk_text_buffer_delete_mark (spell->priv->buffer, spell->priv->mark_insert_end);
      spell->priv->mark_insert_end = NULL;
      gtk_text_buffer_delete_mark (spell->priv->buffer, spell->priv->mark_click);
      spell->priv->mark_click = NULL;

      g_object_unref (spell->priv->buffer);
    }

  spell->priv->buffer = buffer;

  if (spell->priv->buffer)
    {
      g_object_ref (spell->priv->buffer);

      g_signal_connect (spell->priv->buffer, "insert-text",
                        G_CALLBACK (insert_text_before), spell);
      g_signal_connect_after (spell->priv->buffer, "insert-text",
                        G_CALLBACK (insert_text_after), spell);
      g_signal_connect_after (spell->priv->buffer, "delete-range",
                        G_CALLBACK (delete_range_after), spell);
      g_signal_connect (spell->priv->buffer, "mark-set",
                        G_CALLBACK (mark_set), spell);

      GtkTextTagTable *tagtable = gtk_text_buffer_get_tag_table (spell->priv->buffer);
      spell->priv->tag_highlight = gtk_text_tag_table_lookup (tagtable,
                                                     GTK_SPELL_MISSPELLED_TAG);

      if (spell->priv->tag_highlight == NULL)
        {
          spell->priv->tag_highlight = gtk_text_buffer_create_tag (spell->priv->buffer,
                                         GTK_SPELL_MISSPELLED_TAG, "underline",
                                         PANGO_UNDERLINE_ERROR, NULL);
        }


      gtk_text_buffer_get_bounds (spell->priv->buffer, &start, &end);
      spell->priv->mark_insert_start = gtk_text_buffer_create_mark (spell->priv->buffer,
                                        "gtkspell-insert-start", &start, TRUE);
      spell->priv->mark_insert_end = gtk_text_buffer_create_mark (spell->priv->buffer,
                                          "gtkspell-insert-end", &start, TRUE);
      spell->priv->mark_click = gtk_text_buffer_create_mark (spell->priv->buffer,
                                               "gtkspell-click", &start, TRUE);

      spell->priv->deferred_check = FALSE;


      gtk_spell_checker_recheck_all (spell);
    }
}
