gst_audio_test_src_init_sine_table (GstAudioTestSrc * src)
{
  gint i;
  gdouble ang = 0.0;
  gdouble step = M_PI_M2 / 1024.0;
  gdouble amp = src->volume;

  for (i = 0; i < 1024; i++) {
    src->wave_table[i] = sin (ang) * amp;
    ang += step;
  }
}
