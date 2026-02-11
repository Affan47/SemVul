gst_videomixer_release_pad (GstElement * element, GstPad * pad)
{
  GstVideoMixer *mix = NULL;
  GstVideoMixerPad *mixpad;

  mix = GST_VIDEO_MIXER (element);
  GST_VIDEO_MIXER_STATE_LOCK (mix);
  if (G_UNLIKELY (g_slist_find (mix->sinkpads, pad) == NULL)) {
    g_warning ("Unknown pad %s", GST_PAD_NAME (pad));
    goto error;
  }

  mixpad = GST_VIDEO_MIXER_PAD (pad);

  mix->sinkpads = g_slist_remove (mix->sinkpads, pad);
  gst_videomixer_collect_free (mixpad->mixcol);
  gst_collect_pads_remove_pad (mix->collect, pad);
  gst_child_proxy_child_removed (GST_OBJECT (mix), GST_OBJECT (mixpad));

  gst_videomixer_set_master_geometry (mix);
  mix->numpads--;
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);

  gst_element_remove_pad (element, pad);
  return;
error:
  GST_VIDEO_MIXER_STATE_UNLOCK (mix);
}
