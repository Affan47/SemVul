gst_base_transform_init (GstBaseTransform * trans,
    GstBaseTransformClass * bclass)
{
  GstPadTemplate *pad_template;

  GST_DEBUG ("gst_base_transform_init");

  trans->priv = GST_BASE_TRANSFORM_GET_PRIVATE (trans);

  pad_template =
      gst_element_class_get_pad_template (GST_ELEMENT_CLASS (bclass), "sink");
  g_return_if_fail (pad_template != NULL);
  trans->sinkpad = gst_pad_new_from_template (pad_template, "sink");
  gst_pad_set_getcaps_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_getcaps));
  gst_pad_set_acceptcaps_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_acceptcaps));
  gst_pad_set_setcaps_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_setcaps));
  gst_pad_set_event_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_sink_event));
  gst_pad_set_chain_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_chain));
  gst_pad_set_activatepush_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_sink_activate_push));
  gst_pad_set_bufferalloc_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_buffer_alloc));
  gst_pad_set_query_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_query));
  gst_pad_set_query_type_function (trans->sinkpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_query_type));
  gst_element_add_pad (GST_ELEMENT (trans), trans->sinkpad);

  pad_template =
      gst_element_class_get_pad_template (GST_ELEMENT_CLASS (bclass), "src");
  g_return_if_fail (pad_template != NULL);
  trans->srcpad = gst_pad_new_from_template (pad_template, "src");
  gst_pad_set_getcaps_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_getcaps));
  gst_pad_set_acceptcaps_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_acceptcaps));
  gst_pad_set_event_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_src_event));
  gst_pad_set_checkgetrange_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_check_get_range));
  gst_pad_set_getrange_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_getrange));
  gst_pad_set_activatepull_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_src_activate_pull));
  gst_pad_set_query_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_query));
  gst_pad_set_query_type_function (trans->srcpad,
      GST_DEBUG_FUNCPTR (gst_base_transform_query_type));
  gst_element_add_pad (GST_ELEMENT (trans), trans->srcpad);

  trans->transform_lock = g_mutex_new ();
  trans->pending_configure = FALSE;
  trans->priv->qos_enabled = DEFAULT_PROP_QOS;
  trans->cache_caps1 = NULL;
  trans->cache_caps2 = NULL;
  trans->priv->pad_mode = GST_ACTIVATE_NONE;
  trans->priv->gap_aware = FALSE;
  trans->priv->delayed_events = NULL;

  trans->passthrough = FALSE;
  if (bclass->transform == NULL) {

    GST_DEBUG_OBJECT (trans, "setting in_place TRUE");
    trans->always_in_place = TRUE;

    if (bclass->transform_ip == NULL) {
      GST_DEBUG_OBJECT (trans, "setting passthrough TRUE");
      trans->passthrough = TRUE;
    }
  }

  trans->priv->processed = 0;
  trans->priv->dropped = 0;
  trans->priv->force_alloc = TRUE;
}
