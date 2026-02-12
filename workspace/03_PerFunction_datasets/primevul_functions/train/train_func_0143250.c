gst_matroska_demux_peek_cluster_info (GstMatroskaDemux * demux,
    ClusterInfo * cluster, guint64 offset)
{
  demux->common.offset = offset;
  demux->cluster_time = GST_CLOCK_TIME_NONE;

  cluster->offset = offset;
  cluster->size = 0;
  cluster->prev_size = 0;
  cluster->time = GST_CLOCK_TIME_NONE;
  cluster->status = CLUSTER_STATUS_NONE;


  do {
    GstFlowReturn flow;
    guint64 length;
    guint32 id;
    guint needed;

    flow = gst_matroska_read_common_peek_id_length_pull (&demux->common,
        GST_ELEMENT_CAST (demux), &id, &length, &needed);

    if (flow != GST_FLOW_OK)
      break;

    GST_LOG_OBJECT (demux, "Offset %" G_GUINT64_FORMAT ", Element id 0x%x, "
        "size %" G_GUINT64_FORMAT ", needed %d", demux->common.offset, id,
        length, needed);


    if (id == GST_MATROSKA_ID_CLUSTER && cluster->offset != offset)
      break;


    if (id == GST_MATROSKA_ID_ENCRYPTEDBLOCK
        || id == GST_MATROSKA_ID_BLOCKGROUP || id == GST_MATROSKA_ID_BLOCK)
      break;


    if (id == GST_MATROSKA_ID_SIMPLEBLOCK) {
      GstBitReader br;
      guint8 *d, hdr_len, v = 0;

      GST_DEBUG_OBJECT (demux, "SimpleBlock found");


      hdr_len = MIN (21, length);

      flow = gst_matroska_read_common_peek_bytes (&demux->common,
          demux->common.offset, hdr_len, NULL, &d);

      if (flow != GST_FLOW_OK)
        break;

      gst_bit_reader_init (&br, d, hdr_len);


      if (!gst_bit_reader_skip (&br, 8 * needed))
        break;


      if (!bit_reader_skip_ebml_num (&br))
        break;


      if (!gst_bit_reader_skip (&br, 16))
        break;


      if (!gst_bit_reader_get_bits_uint8 (&br, &v, 8))
        break;

      if ((v & 0x80) != 0)
        cluster->status = CLUSTER_STATUS_STARTS_WITH_KEYFRAME;
      else
        cluster->status = CLUSTER_STATUS_STARTS_WITH_DELTAUNIT;

      break;
    }

    flow = gst_matroska_demux_parse_id (demux, id, length, needed);

    if (flow != GST_FLOW_OK)
      break;

    switch (id) {
      case GST_MATROSKA_ID_CLUSTER:
        if (length == G_MAXUINT64)
          cluster->size = 0;
        else
          cluster->size = length + needed;
        break;
      case GST_MATROSKA_ID_PREVSIZE:
        cluster->prev_size = demux->cluster_prevsize;
        break;
      case GST_MATROSKA_ID_CLUSTERTIMECODE:
        cluster->time = demux->cluster_time * demux->common.time_scale;
        break;
      case GST_MATROSKA_ID_SILENTTRACKS:
      case GST_EBML_ID_CRC32:

        break;
      default:
        GST_WARNING_OBJECT (demux, "Unknown ebml id 0x%08x (possibly garbage), "
            "bailing out", id);
        goto out;
    }
  } while (demux->common.offset - offset < MAX_CLUSTER_INFO_PROBE_LENGTH);

out:

  GST_INFO_OBJECT (demux, "Cluster @ %" G_GUINT64_FORMAT ": "
      "time %" GST_TIME_FORMAT ", size %" G_GUINT64_FORMAT ", "
      "prev_size %" G_GUINT64_FORMAT ", %s", cluster->offset,
      GST_TIME_ARGS (cluster->time), cluster->size, cluster->prev_size,
      cluster_status_get_nick (cluster->status));


  return cluster->time != GST_CLOCK_TIME_NONE;
}
