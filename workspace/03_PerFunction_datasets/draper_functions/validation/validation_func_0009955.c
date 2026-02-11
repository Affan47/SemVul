_gtr_po_load_ensure_utf8 (GtrPo * po, GError ** error)
{
  GMappedFile *mapped;
  const gchar *content;
  gboolean utf8_valid;
  gchar *filename;
  gsize size;

  filename = g_file_get_path (po->priv->location);
  mapped = g_mapped_file_new (filename, FALSE, error);
  g_free (filename);

  if (!mapped)
    return FALSE;

  content = g_mapped_file_get_contents (mapped);
  size = g_mapped_file_get_length (mapped);

  utf8_valid = g_utf8_validate (content, size, NULL);

  if (!_gtr_po_load (po, po->priv->location, error))
    {
      g_mapped_file_unref (mapped);
      return FALSE;
    }

  if (!utf8_valid &&
      po->priv->header)
    {
      gchar *charset = NULL;

      if (po->priv->header)
        charset = gtr_header_get_charset (po->priv->header);

      if (charset && *charset && strcmp (charset, "UTF-8") != 0)
        {
          GOutputStream *converter_stream, *stream;
          GCharsetConverter *converter;
          GIOStream *iostream;
          GFile *tmp;


          converter = g_charset_converter_new ("UTF-8", charset, NULL);

          if (!converter)
            {
              g_set_error (error,
                           GTR_PO_ERROR,
                           GTR_PO_ERROR_ENCODING,
                           _("Could not convert from charset '%s' to UTF-8"),
                           charset);
              g_mapped_file_unref (mapped);
              g_free (charset);
              return FALSE;
            }

          g_free (charset);
          tmp = g_file_new_tmp ("gtranslator-XXXXXX.po",
                                (GFileIOStream **) &iostream,
                                NULL);

          if (!tmp)
            {
              g_set_error (error,
                           GTR_PO_ERROR,
                           GTR_PO_ERROR_ENCODING,
                           _("Could not store temporary "
                             "file for encoding conversion"));
              g_mapped_file_unref (mapped);
              g_object_unref (converter);
              return FALSE;
            }

          stream = g_io_stream_get_output_stream (iostream);
          converter_stream =
            g_converter_output_stream_new (stream,
                                           G_CONVERTER (converter));


          if (!g_output_stream_write_all (converter_stream,
                                          content, size, NULL,
                                          NULL, NULL))
            {
              g_set_error (error,
                           GTR_PO_ERROR,
                           GTR_PO_ERROR_ENCODING,
                           _("Could not store temporary "
                             "file for encoding conversion"));
              g_object_unref (converter_stream);
              g_object_unref (iostream);
              g_object_unref (converter);
              g_mapped_file_unref (mapped);
              return FALSE;
            }

          g_object_unref (converter_stream);
          g_object_unref (iostream);
          g_object_unref (converter);


          if (!_gtr_po_load (po, tmp, error))
            {
              g_mapped_file_unref (mapped);
              return FALSE;
            }


          if (po->priv->header)
            gtr_header_set_charset (po->priv->header, "UTF-8");

          utf8_valid = TRUE;
        }
    }

  g_mapped_file_unref (mapped);

  if (!utf8_valid)
    {
      g_set_error (error,
                   GTR_PO_ERROR,
                   GTR_PO_ERROR_ENCODING,
                   _("All attempt to convert the file to UTF-8 has failed, "
                     "use the msgconv or iconv command line tools before "
                     "opening this file with gtranslator"));
      return FALSE;
    }

  return TRUE;
}
