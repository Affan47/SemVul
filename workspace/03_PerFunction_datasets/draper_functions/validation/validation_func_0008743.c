gst_base_parse_init (GstBaseParse * parse, GstBaseParseClass * bclass)
{
  GstPadTemplate *pad_template;

  GST_DEBUG_OBJECT (parse, "gst_base_parse_init");

  parse->priv = GST_BASE_PARSE_GET_PRIVATE (parse);

  pad_template =
      gst_element_class_get_pad_template (GST_ELEMENT_CLASS (bclass), "sink");
  g_return_if_fail (pad_template != NULL);
  parse->sinkpad = gst_pad_new_from_template (pad_template, "sink");
  gst_pad_set_event_function (parse->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_sink_event));
  gst_pad_set_query_function (parse->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_sink_query));
  gst_pad_set_chain_function (parse->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_chain));
  gst_pad_set_activate_function (parse->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_sink_activate));
  gst_pad_set_activatemode_function (parse->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_sink_activate_mode));
  GST_PAD_SET_PROXY_ALLOCATION (parse->sinkpad);
  gst_element_add_pad (GST_ELEMENT (parse), parse->sinkpad);

  GST_DEBUG_OBJECT (parse, "sinkpad created");

  pad_template =
      gst_element_class_get_pad_template (GST_ELEMENT_CLASS (bclass), "src");
  g_return_if_fail (pad_template != NULL);
  parse->srcpad = gst_pad_new_from_template (pad_template, "src");
  gst_pad_set_event_function (parse->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_src_event));
  gst_pad_set_query_function (parse->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_parse_src_query));
  gst_pad_use_fixed_caps (parse->srcpad);
  gst_element_add_pad (GST_ELEMENT (parse), parse->srcpad);
  GST_DEBUG_OBJECT (parse, "src created");

  g_queue_init (&parse->priv->queued_frames);

  parse->priv->adapter = gst_adapter_new ();

  parse->priv->pad_mode = GST_PAD_MODE_NONE;

  g_mutex_init (&parse->priv->index_lock);


  gst_base_parse_reset (parse);
  GST_DEBUG_OBJECT (parse, "init ok");

  GST_OBJECT_FLAG_SET (parse, GST_ELEMENT_FLAG_INDEXABLE);
}
