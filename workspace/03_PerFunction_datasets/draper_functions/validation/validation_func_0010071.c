gst_audio_fir_filter_setup (GstAudioFilter * base, const GstAudioInfo * info)
{
  GstAudioFIRFilter *self = GST_AUDIO_FIR_FILTER (base);
  gint new_rate = GST_AUDIO_INFO_RATE (info);

  if (GST_AUDIO_FILTER_RATE (self) != new_rate) {
    g_signal_emit (G_OBJECT (self),
        gst_audio_fir_filter_signals[SIGNAL_RATE_CHANGED], 0, new_rate);
  }

  return GST_AUDIO_FILTER_CLASS (parent_class)->setup (base, info);
}
