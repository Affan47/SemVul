mpegts_pmt_stream_info_finalize (GObject * object)
{
  MpegTsPmtStreamInfo *info = MPEGTS_PMT_STREAM_INFO (object);

  g_value_array_free (info->languages);
  g_value_array_free (info->descriptors);

  GST_CALL_PARENT (G_OBJECT_CLASS, finalize, (object));
}
