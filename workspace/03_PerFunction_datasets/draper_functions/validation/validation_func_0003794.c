gst_decode_bin_init (GstDecodeBin * decode_bin)
{

  decode_bin->factories_lock = g_mutex_new ();


  decode_bin->typefind = gst_element_factory_make ("typefind", "typefind");
  if (!decode_bin->typefind) {
    g_warning ("can't find typefind element, decodebin will not work");
  } else {
    GstPad *pad;
    GstPad *gpad;
    GstPadTemplate *pad_tmpl;


    if (!gst_bin_add (GST_BIN (decode_bin), decode_bin->typefind)) {
      g_warning ("Could not add typefind element, decodebin will not work");
      gst_object_unref (decode_bin->typefind);
      decode_bin->typefind = NULL;
    }


    pad = gst_element_get_static_pad (decode_bin->typefind, "sink");


    pad_tmpl = gst_static_pad_template_get (&decoder_bin_sink_template);


    gpad = gst_ghost_pad_new_from_template ("sink", pad, pad_tmpl);
    gst_pad_set_active (gpad, TRUE);
    gst_element_add_pad (GST_ELEMENT (decode_bin), gpad);

    gst_object_unref (pad_tmpl);
    gst_object_unref (pad);


    decode_bin->have_type_id =
        g_signal_connect (G_OBJECT (decode_bin->typefind), "have-type",
        G_CALLBACK (type_found), decode_bin);
  }

  decode_bin->expose_lock = g_mutex_new ();
  decode_bin->decode_chain = NULL;

  decode_bin->dyn_lock = g_mutex_new ();
  decode_bin->shutdown = FALSE;
  decode_bin->blocked_pads = NULL;

  decode_bin->subtitle_lock = g_mutex_new ();

  decode_bin->encoding = g_strdup (DEFAULT_SUBTITLE_ENCODING);
  decode_bin->caps = gst_static_caps_get (&default_raw_caps);
  decode_bin->use_buffering = DEFAULT_USE_BUFFERING;
  decode_bin->low_percent = DEFAULT_LOW_PERCENT;
  decode_bin->high_percent = DEFAULT_HIGH_PERCENT;

  decode_bin->max_size_bytes = DEFAULT_MAX_SIZE_BYTES;
  decode_bin->max_size_buffers = DEFAULT_MAX_SIZE_BUFFERS;
  decode_bin->max_size_time = DEFAULT_MAX_SIZE_TIME;

  decode_bin->expose_allstreams = DEFAULT_EXPOSE_ALL_STREAMS;
}
