gst_matroska_demux_check_read_size (GstMatroskaDemux * demux, guint64 bytes)
{
  if (G_UNLIKELY (bytes > MAX_BLOCK_SIZE)) {


    if (demux->streaming) {

      GST_ELEMENT_ERROR (demux, STREAM, DEMUX, (NULL),
          ("reading large block of size %" G_GUINT64_FORMAT " not supported; "
              "file might be corrupt.", bytes));
      return GST_FLOW_ERROR;
    } else {

      GST_DEBUG_OBJECT (demux,
          "too large block of size %" G_GUINT64_FORMAT, bytes);
      return GST_FLOW_ERROR;
    }
  } else {
    return GST_FLOW_OK;
  }
}
