gst_asf_demux_check_buffer_is_header (GstASFDemux * demux, GstBuffer * buf)
{
  AsfObject obj;
  g_assert (buf != NULL);

  GST_LOG_OBJECT (demux, "Checking if buffer is a header");


  if (GST_BUFFER_SIZE (buf) < ASF_OBJECT_HEADER_SIZE)
    return FALSE;


  asf_demux_peek_object (demux, GST_BUFFER_DATA (buf),
      ASF_OBJECT_HEADER_SIZE, &obj, TRUE);
  if (obj.id == ASF_OBJ_HEADER) {
    return TRUE;
  }
  return FALSE;
}
