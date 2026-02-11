gst_qtdemux_src_convert (GstPad * pad, GstFormat src_format, gint64 src_value,
    GstFormat dest_format, gint64 * dest_value)
{
  gboolean res = TRUE;
  QtDemuxStream *stream = gst_pad_get_element_private (pad);
  GstQTDemux *qtdemux = GST_QTDEMUX (gst_pad_get_parent (pad));
  gint32 index;

  if (stream->subtype != FOURCC_vide) {
    res = FALSE;
    goto done;
  }

  switch (src_format) {
    case GST_FORMAT_TIME:
      switch (dest_format) {
        case GST_FORMAT_BYTES:{
          index = gst_qtdemux_find_index_linear (qtdemux, stream, src_value);
          if (-1 == index)
            return FALSE;

          *dest_value = stream->samples[index].offset;

          GST_DEBUG_OBJECT (qtdemux, "Format Conversion Time->Offset :%"
              GST_TIME_FORMAT "->%" G_GUINT64_FORMAT,
              GST_TIME_ARGS (src_value), *dest_value);
          break;
        }
        default:
          res = FALSE;
          break;
      }
      break;
    case GST_FORMAT_BYTES:
      switch (dest_format) {
        case GST_FORMAT_TIME:{
          index =
              gst_qtdemux_find_index_for_given_media_offset_linear (qtdemux,
              stream, src_value);

          if (-1 == index)
            return FALSE;

          *dest_value =
              gst_util_uint64_scale (stream->samples[index].timestamp,
              GST_SECOND, stream->timescale);
          GST_DEBUG_OBJECT (qtdemux, "Format Conversion Offset->Time :%"
              G_GUINT64_FORMAT "->%" GST_TIME_FORMAT,
              src_value, GST_TIME_ARGS (*dest_value));
          break;
        }
        default:
          res = FALSE;
          break;
      }
      break;
    default:
      res = FALSE;
  }

done:
  gst_object_unref (qtdemux);

  return res;
}
