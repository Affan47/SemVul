gst_ivtc_retire_fields (GstIvtc * ivtc, int n_fields)
{
  int i;

  if (n_fields == 0)
    return;

  for (i = 0; i < n_fields; i++) {
    gst_video_frame_unmap (&ivtc->fields[i].frame);
    gst_buffer_unref (ivtc->fields[i].buffer);
  }

  memmove (ivtc->fields, ivtc->fields + n_fields,
      sizeof (GstIvtcField) * (ivtc->n_fields - n_fields));
  ivtc->n_fields -= n_fields;
}
