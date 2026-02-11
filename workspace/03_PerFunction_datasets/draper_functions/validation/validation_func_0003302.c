fs_nice_transmitter_free_gst_stream (FsNiceTransmitter *self,
    NiceGstStream *ns)
{
  guint c;

  for (c = 1; c <= self->components; c++)
  {
    if (ns->nicesrcs[c])
    {
      GstStateChangeReturn ret;
      if (!gst_bin_remove (GST_BIN (self->priv->gst_src), ns->nicesrcs[c]))
        GST_ERROR ("Could not remove nicesrc element from transmitter source");
      ret = gst_element_set_state (ns->nicesrcs[c], GST_STATE_NULL);
      if (ret != GST_STATE_CHANGE_SUCCESS)
        GST_ERROR ("Error changing state of nicesrc: %s",
            gst_element_state_change_return_get_name (ret));
      gst_object_unref (ns->nicesrcs[c]);
    }

    if (ns->requested_funnel_pads[c])
    {
      gst_element_release_request_pad (self->priv->src_funnels[c],
          ns->requested_funnel_pads[c]);
      gst_object_unref (ns->requested_funnel_pads[c]);
    }

    if (ns->nicesinks[c])
    {
      remove_sink (self, ns, c);
      gst_object_unref (ns->nicesinks[c]);
    }

    if (ns->recvonly_filters[c])
    {
      GstStateChangeReturn ret;

      gst_element_set_locked_state (ns->recvonly_filters[c], TRUE);
      ret = gst_element_set_state (ns->recvonly_filters[c], GST_STATE_NULL);
      if (ret != GST_STATE_CHANGE_SUCCESS)
        GST_ERROR ("Error changing state of nicesink: %s",
            gst_element_state_change_return_get_name (ret));
      if (!gst_bin_remove (GST_BIN (self->priv->gst_sink),
              ns->recvonly_filters[c]))
        GST_ERROR ("Could not remove the recvonly filter element from"
            " the transmitter sink");
    }
  }

  g_free (ns->nicesrcs);
  g_free (ns->nicesinks);
  g_free (ns->recvonly_filters);
  g_free (ns->requested_tee_pads);
  g_free (ns->requested_funnel_pads);
  g_free (ns->probe_ids);
  g_mutex_free (ns->mutex);
  g_slice_free (NiceGstStream, ns);
}
