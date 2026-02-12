qtdemux_parse_tree (GstQTDemux * qtdemux)
{
  GNode *mvhd;
  GNode *trak;
  GNode *udta;
  GNode *mvex;
  GstClockTime duration;
  GNode *pssh;
  guint64 creation_time;
  GstDateTime *datetime = NULL;
  gint version;


  if (!qtdemux->tag_list) {
    qtdemux->tag_list = gst_tag_list_new_empty ();
    gst_tag_list_set_scope (qtdemux->tag_list, GST_TAG_SCOPE_GLOBAL);
  } else {
    qtdemux->tag_list = gst_tag_list_make_writable (qtdemux->tag_list);
  }

  mvhd = qtdemux_tree_get_child_by_type (qtdemux->moov_node, FOURCC_mvhd);
  if (mvhd == NULL) {
    GST_LOG_OBJECT (qtdemux, "No mvhd node found, looking for redirects.");
    return qtdemux_parse_redirects (qtdemux);
  }

  version = QT_UINT8 ((guint8 *) mvhd->data + 8);
  if (version == 1) {
    creation_time = QT_UINT64 ((guint8 *) mvhd->data + 12);
    qtdemux->timescale = QT_UINT32 ((guint8 *) mvhd->data + 28);
    qtdemux->duration = QT_UINT64 ((guint8 *) mvhd->data + 32);
  } else if (version == 0) {
    creation_time = QT_UINT32 ((guint8 *) mvhd->data + 12);
    qtdemux->timescale = QT_UINT32 ((guint8 *) mvhd->data + 20);
    qtdemux->duration = QT_UINT32 ((guint8 *) mvhd->data + 24);
  } else {
    GST_WARNING_OBJECT (qtdemux, "Unhandled mvhd version %d", version);
    return FALSE;
  }


  if (creation_time != 0) {

    if (creation_time >= QTDEMUX_SECONDS_FROM_1904_TO_1970) {
      GTimeVal now;

      creation_time -= QTDEMUX_SECONDS_FROM_1904_TO_1970;

      g_get_current_time (&now);
      if (now.tv_sec + 24 * 3600 < creation_time) {
        GST_DEBUG_OBJECT (qtdemux, "discarding bogus future creation time");
      } else {
        datetime = gst_date_time_new_from_unix_epoch_utc (creation_time);
      }
    } else {
      GDateTime *base_dt = g_date_time_new_utc (1904, 1, 1, 0, 0, 0);
      GDateTime *dt, *dt_local;

      dt = g_date_time_add_seconds (base_dt, creation_time);
      dt_local = g_date_time_to_local (dt);
      datetime = gst_date_time_new_from_g_date_time (dt_local);

      g_date_time_unref (base_dt);
      g_date_time_unref (dt);
    }
  }
  if (datetime) {

    gst_tag_list_add (qtdemux->tag_list, GST_TAG_MERGE_KEEP, GST_TAG_DATE_TIME,
        datetime, NULL);
    gst_date_time_unref (datetime);
  }

  GST_INFO_OBJECT (qtdemux, "timescale: %u", qtdemux->timescale);
  GST_INFO_OBJECT (qtdemux, "duration: %" G_GUINT64_FORMAT, qtdemux->duration);


  mvex = qtdemux_tree_get_child_by_type (qtdemux->moov_node, FOURCC_mvex);
  if (mvex) {
    GNode *mehd;
    GstByteReader mehd_data;


    qtdemux->fragmented = TRUE;


    mehd = qtdemux_tree_get_child_by_type_full (mvex, FOURCC_mehd, &mehd_data);
    if (mehd)
      qtdemux_parse_mehd (qtdemux, &mehd_data);
  }


  gst_qtdemux_get_duration (qtdemux, &duration);
  if (duration) {
    qtdemux->segment.duration = duration;


    qtdemux->segment.stop = duration;
  }


  trak = qtdemux_tree_get_child_by_type (qtdemux->moov_node, FOURCC_trak);
  while (trak) {
    qtdemux_parse_trak (qtdemux, trak);

    trak = qtdemux_tree_get_sibling_by_type (trak, FOURCC_trak);
  }

  if (!qtdemux->tag_list) {
    GST_DEBUG_OBJECT (qtdemux, "new tag list");
    qtdemux->tag_list = gst_tag_list_new_empty ();
    gst_tag_list_set_scope (qtdemux->tag_list, GST_TAG_SCOPE_GLOBAL);
  } else {
    qtdemux->tag_list = gst_tag_list_make_writable (qtdemux->tag_list);
  }


  udta = qtdemux_tree_get_child_by_type (qtdemux->moov_node, FOURCC_udta);
  if (udta) {
    qtdemux_parse_udta (qtdemux, qtdemux->tag_list, udta);
  } else {
    GST_LOG_OBJECT (qtdemux, "No udta node found.");
  }


  udta = qtdemux_tree_get_child_by_type (qtdemux->moov_node, FOURCC_meta);
  if (udta) {
    GST_DEBUG_OBJECT (qtdemux, "Parsing meta box for tags.");
    qtdemux_parse_udta (qtdemux, qtdemux->tag_list, udta);
  } else {
    GST_LOG_OBJECT (qtdemux, "No meta node found.");
  }


  pssh = qtdemux_tree_get_child_by_type (qtdemux->moov_node, FOURCC_pssh);
  while (pssh) {
    GST_LOG_OBJECT (qtdemux, "Parsing pssh box.");
    qtdemux_parse_pssh (qtdemux, pssh);
    pssh = qtdemux_tree_get_sibling_by_type (pssh, FOURCC_pssh);
  }

  qtdemux->tag_list = qtdemux_add_container_format (qtdemux, qtdemux->tag_list);

  return TRUE;
}
