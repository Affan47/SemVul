theora_enc_start (GstVideoEncoder * benc)
{
  GstTheoraEnc *enc;

  GST_DEBUG_OBJECT (benc, "start: init theora");
  enc = GST_THEORA_ENC (benc);

  if (enc->multipass_mode >= MULTIPASS_MODE_FIRST_PASS) {
    GError *err = NULL;

    if (!enc->multipass_cache_file) {
      GST_ELEMENT_ERROR (enc, LIBRARY, SETTINGS, (NULL), (NULL));
      return FALSE;
    }
    enc->multipass_cache_fd =
        g_io_channel_new_file (enc->multipass_cache_file,
        (enc->multipass_mode == MULTIPASS_MODE_FIRST_PASS ? "w" : "r"), &err);

    if (enc->multipass_mode == MULTIPASS_MODE_SECOND_PASS)
      enc->multipass_cache_adapter = gst_adapter_new ();

    if (!enc->multipass_cache_fd) {
      GST_ELEMENT_ERROR (enc, RESOURCE, OPEN_READ, (NULL),
          ("Failed to open multipass cache file: %s", err->message));
      g_error_free (err);
      return FALSE;
    }

    g_io_channel_set_encoding (enc->multipass_cache_fd, NULL, NULL);
  }

  enc->packetno = 0;
  enc->initialised = FALSE;

  return TRUE;
}
