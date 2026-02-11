gst_iir_equalizer_compute_frequencies (GstIirEqualizer * equ, guint new_count)
{
  guint old_count, i;
  gdouble freq0, freq1, step;
  gchar name[20];

  if (equ->freq_band_count == new_count)
    return;

  BANDS_LOCK (equ);

  if (G_UNLIKELY (equ->freq_band_count == new_count)) {
    BANDS_UNLOCK (equ);
    return;
  }

  old_count = equ->freq_band_count;
  equ->freq_band_count = new_count;
  GST_DEBUG ("bands %u -> %u", old_count, new_count);

  if (old_count < new_count) {

    equ->bands = g_realloc (equ->bands, sizeof (GstObject *) * new_count);
    for (i = old_count; i < new_count; i++) {

      sprintf (name, "band%u", i);
      equ->bands[i] = g_object_new (GST_TYPE_IIR_EQUALIZER_BAND,
          "name", name, NULL);
      GST_DEBUG ("adding band[%d]=%p", i, equ->bands[i]);

      gst_object_set_parent (GST_OBJECT (equ->bands[i]), GST_OBJECT (equ));
      gst_child_proxy_child_added (GST_CHILD_PROXY (equ),
          G_OBJECT (equ->bands[i]), name);
    }
  } else {

    for (i = new_count; i < old_count; i++) {
      GST_DEBUG ("removing band[%d]=%p", i, equ->bands[i]);
      gst_child_proxy_child_removed (GST_CHILD_PROXY (equ),
          G_OBJECT (equ->bands[i]), GST_OBJECT_NAME (equ->bands[i]));
      gst_object_unparent (GST_OBJECT (equ->bands[i]));
      equ->bands[i] = NULL;
    }
  }

  alloc_history (equ, GST_AUDIO_FILTER_INFO (equ));


  step = pow (HIGHEST_FREQ / LOWEST_FREQ, 1.0 / new_count);
  freq0 = LOWEST_FREQ;
  for (i = 0; i < new_count; i++) {
    freq1 = freq0 * step;

    if (i == 0)
      equ->bands[i]->type = BAND_TYPE_LOW_SHELF;
    else if (i == new_count - 1)
      equ->bands[i]->type = BAND_TYPE_HIGH_SHELF;
    else
      equ->bands[i]->type = BAND_TYPE_PEAK;

    equ->bands[i]->freq = freq0 + ((freq1 - freq0) / 2.0);
    equ->bands[i]->width = freq1 - freq0;
    GST_DEBUG ("band[%2d] = '%lf'", i, equ->bands[i]->freq);

    g_object_notify (G_OBJECT (equ->bands[i]), "bandwidth");
    g_object_notify (G_OBJECT (equ->bands[i]), "freq");
    g_object_notify (G_OBJECT (equ->bands[i]), "type");


    freq0 = freq1;
  }

  equ->need_new_coefficients = TRUE;
  BANDS_UNLOCK (equ);
}
