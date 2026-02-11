gst_flv_mux_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * req_name, const GstCaps * caps)
{
  GstElementClass *klass = GST_ELEMENT_GET_CLASS (element);
  GstFlvMux *mux = GST_FLV_MUX (element);
  GstFlvPad *cpad;
  GstPad *pad = NULL;
  const gchar *name = NULL;
  gboolean video;

  if (mux->state != GST_FLV_MUX_STATE_HEADER) {
    GST_WARNING_OBJECT (mux, "Can't request pads after writing header");
    return NULL;
  }

  if (templ == gst_element_class_get_pad_template (klass, "audio")) {
    if (mux->have_audio) {
      GST_WARNING_OBJECT (mux, "Already have an audio pad");
      return NULL;
    }
    mux->have_audio = TRUE;
    name = "audio";
    video = FALSE;
  } else if (templ == gst_element_class_get_pad_template (klass, "video")) {
    if (mux->have_video) {
      GST_WARNING_OBJECT (mux, "Already have a video pad");
      return NULL;
    }
    mux->have_video = TRUE;
    name = "video";
    video = TRUE;
  } else {
    GST_WARNING_OBJECT (mux, "Invalid template");
    return NULL;
  }

  pad = gst_pad_new_from_template (templ, name);
  cpad = (GstFlvPad *) gst_collect_pads_add_pad (mux->collect, pad,
      sizeof (GstFlvPad), NULL, TRUE);

  cpad->audio_codec_data = NULL;
  cpad->video_codec_data = NULL;
  gst_flv_mux_reset_pad (mux, cpad, video);

  gst_pad_set_active (pad, TRUE);
  gst_element_add_pad (element, pad);

  return pad;
}
