gst_au_parse_src_query (GstPad * pad, GstQuery * query)
{
  GstAuParse *auparse;
  gboolean ret = FALSE;

  auparse = GST_AU_PARSE (gst_pad_get_parent (pad));

  switch (GST_QUERY_TYPE (query)) {
    case GST_QUERY_DURATION:{
      GstFormat bformat = GST_FORMAT_BYTES;
      GstFormat format;
      gint64 len, val;

      gst_query_parse_duration (query, &format, NULL);
      if (!gst_pad_query_peer_duration (auparse->sinkpad, &bformat, &len)) {
        GST_DEBUG_OBJECT (auparse, "failed to query upstream length");
        break;
      }
      GST_OBJECT_LOCK (auparse);
      len -= auparse->offset;
      GST_OBJECT_UNLOCK (auparse);

      ret = gst_au_parse_src_convert (auparse, bformat, len, format, &val);

      if (ret) {
        gst_query_set_duration (query, format, val);
      }
      break;
    }
    case GST_QUERY_POSITION:{
      GstFormat bformat = GST_FORMAT_BYTES;
      GstFormat format;
      gint64 pos, val;

      gst_query_parse_position (query, &format, NULL);
      if (!gst_pad_query_peer_position (auparse->sinkpad, &bformat, &pos)) {
        GST_DEBUG_OBJECT (auparse, "failed to query upstream position");
        break;
      }
      GST_OBJECT_LOCK (auparse);
      pos -= auparse->offset;
      GST_OBJECT_UNLOCK (auparse);

      ret = gst_au_parse_src_convert (auparse, GST_FORMAT_BYTES, pos,
          format, &val);

      if (ret) {
        gst_query_set_position (query, format, val);
      }
      break;
    }
    case GST_QUERY_SEEKING:{
      GstFormat format;

      gst_query_parse_seeking (query, &format, NULL, NULL, NULL);


      gst_query_set_seeking (query, format, TRUE, 0, GST_CLOCK_TIME_NONE);
      ret = TRUE;
      break;
    }
    default:
      ret = gst_pad_query_default (pad, query);
      break;
  }

  gst_object_unref (auparse);
  return ret;
}
