qtdemux_stbl_init (GstQTDemux * qtdemux, QtDemuxStream * stream, GNode * stbl)
{
  stream->stbl_index = -1;
  stream->sample_index = -1;


  if (!qtdemux_tree_get_child_by_type_full (stbl, FOURCC_stts, &stream->stts))
    goto corrupt_file;


  stream->stts.data = g_memdup (stream->stts.data, stream->stts.size);


  if (!gst_byte_reader_skip (&stream->stts, 1 + 3) ||
      !gst_byte_reader_get_uint32_be (&stream->stts, &stream->n_sample_times))
    goto corrupt_file;
  GST_LOG_OBJECT (qtdemux, "%u timestamp blocks", stream->n_sample_times);


  if (!qt_atom_parser_has_chunks (&stream->stts, stream->n_sample_times, 8)) {
    stream->n_sample_times = gst_byte_reader_get_remaining (&stream->stts) / 8;
    GST_LOG_OBJECT (qtdemux, "overriding to %u timestamp blocks",
        stream->n_sample_times);
    if (!stream->n_sample_times)
      goto corrupt_file;
  }


  stream->stps_present = FALSE;
  if ((stream->stss_present =
          ! !qtdemux_tree_get_child_by_type_full (stbl, FOURCC_stss,
              &stream->stss) ? TRUE : FALSE) == TRUE) {

    stream->stss.data = g_memdup (stream->stss.data, stream->stss.size);


    if (!gst_byte_reader_skip (&stream->stss, 1 + 3) ||
        !gst_byte_reader_get_uint32_be (&stream->stss, &stream->n_sample_syncs))
      goto corrupt_file;

    if (stream->n_sample_syncs) {

      if (!qt_atom_parser_has_chunks (&stream->stss, stream->n_sample_syncs, 4))
        goto corrupt_file;
    }


    if ((stream->stps_present =
            ! !qtdemux_tree_get_child_by_type_full (stbl, FOURCC_stps,
                &stream->stps) ? TRUE : FALSE) == TRUE) {

      stream->stps.data = g_memdup (stream->stps.data, stream->stps.size);


      if (!gst_byte_reader_skip (&stream->stps, 1 + 3) ||
          !gst_byte_reader_get_uint32_be (&stream->stps,
              &stream->n_sample_partial_syncs))
        goto corrupt_file;


      if (stream->n_sample_partial_syncs) {

        if (!qt_atom_parser_has_chunks (&stream->stps,
                stream->n_sample_partial_syncs, 4))
          goto corrupt_file;
      }
    }
  }


  if (!qtdemux_tree_get_child_by_type_full (stbl, FOURCC_stsz, &stream->stsz))
    goto no_samples;


  stream->stsz.data = g_memdup (stream->stsz.data, stream->stsz.size);


  if (!gst_byte_reader_skip (&stream->stsz, 1 + 3) ||
      !gst_byte_reader_get_uint32_be (&stream->stsz, &stream->sample_size))
    goto corrupt_file;

  if (!gst_byte_reader_get_uint32_be (&stream->stsz, &stream->n_samples))
    goto corrupt_file;

  if (!stream->n_samples)
    goto no_samples;


  if (!qtdemux_tree_get_child_by_type_full (stbl, FOURCC_stsc, &stream->stsc))
    goto corrupt_file;


  stream->stsc.data = g_memdup (stream->stsc.data, stream->stsc.size);


  if (!gst_byte_reader_skip (&stream->stsc, 1 + 3) ||
      !gst_byte_reader_get_uint32_be (&stream->stsc,
          &stream->n_samples_per_chunk))
    goto corrupt_file;

  GST_DEBUG_OBJECT (qtdemux, "n_samples_per_chunk %u",
      stream->n_samples_per_chunk);


  if (!qt_atom_parser_has_chunks (&stream->stsc, stream->n_samples_per_chunk,
          12))
    goto corrupt_file;


  if (qtdemux_tree_get_child_by_type_full (stbl, FOURCC_stco, &stream->stco))
    stream->co_size = sizeof (guint32);
  else if (qtdemux_tree_get_child_by_type_full (stbl, FOURCC_co64,
          &stream->stco))
    stream->co_size = sizeof (guint64);
  else
    goto corrupt_file;


  stream->stco.data = g_memdup (stream->stco.data, stream->stco.size);


  if (!gst_byte_reader_skip (&stream->stco, 1 + 3))
    goto corrupt_file;


  stream->chunks_are_samples = stream->sample_size && !stream->sampled;
  if (stream->chunks_are_samples) {

    if (!gst_byte_reader_get_uint32_be (&stream->stco, &stream->n_samples))
      goto corrupt_file;
  } else {

    if (!gst_byte_reader_skip (&stream->stco, 4))
      goto corrupt_file;


    if (!stream->sample_size) {

      if (!qt_atom_parser_has_chunks (&stream->stsz, stream->n_samples, 4))
        goto corrupt_file;
    }
  }

  GST_DEBUG_OBJECT (qtdemux, "allocating n_samples %u * %u (%.2f MB)",
      stream->n_samples, (guint) sizeof (QtDemuxSample),
      stream->n_samples * sizeof (QtDemuxSample) / (1024.0 * 1024.0));

  if (stream->n_samples >=
      QTDEMUX_MAX_SAMPLE_INDEX_SIZE / sizeof (QtDemuxSample)) {
    GST_WARNING_OBJECT (qtdemux, "not allocating index of %d samples, would "
        "be larger than %uMB (broken file?)", stream->n_samples,
        QTDEMUX_MAX_SAMPLE_INDEX_SIZE >> 20);
    return FALSE;
  }

  g_assert (stream->samples == NULL);
  stream->samples = g_try_new0 (QtDemuxSample, stream->n_samples);
  if (!stream->samples) {
    GST_WARNING_OBJECT (qtdemux, "failed to allocate %d samples",
        stream->n_samples);
    return FALSE;
  }


  if ((stream->ctts_present =
          ! !qtdemux_tree_get_child_by_type_full (stbl, FOURCC_ctts,
              &stream->ctts) ? TRUE : FALSE) == TRUE) {
    GstByteReader cslg = GST_BYTE_READER_INIT (NULL, 0);


    stream->ctts.data = g_memdup (stream->ctts.data, stream->ctts.size);


    if (!gst_byte_reader_skip (&stream->ctts, 1 + 3)
        || !gst_byte_reader_get_uint32_be (&stream->ctts,
            &stream->n_composition_times))
      goto corrupt_file;


    if (!qt_atom_parser_has_chunks (&stream->ctts, stream->n_composition_times,
            4 + 4))
      goto corrupt_file;


    if (qtdemux_tree_get_child_by_type_full (stbl, FOURCC_cslg, &cslg)) {
      if (!gst_byte_reader_skip (&cslg, 1 + 3)
          || !gst_byte_reader_get_uint32_be (&cslg, &stream->cslg_shift)) {
        g_free ((gpointer) cslg.data);
        goto corrupt_file;
      }
    } else {
      gint32 cslg_least = 0;
      guint num_entries, pos;
      gint i;

      pos = gst_byte_reader_get_pos (&stream->ctts);
      num_entries = stream->n_composition_times;

      stream->cslg_shift = 0;

      for (i = 0; i < num_entries; i++) {
        gint32 offset;

        gst_byte_reader_skip_unchecked (&stream->ctts, 4);
        offset = gst_byte_reader_get_int32_be_unchecked (&stream->ctts);

        if (offset < cslg_least)
          cslg_least = offset;
      }

      if (cslg_least < 0)
        stream->cslg_shift = ABS (cslg_least);
      else
        stream->cslg_shift = 0;


      gst_byte_reader_set_pos (&stream->ctts, pos);
    }
  } else {


    stream->cslg_shift = 0;
  }

  return TRUE;

corrupt_file:
  {
    GST_ELEMENT_ERROR (qtdemux, STREAM, DEMUX,
        (_("This file is corrupt and cannot be played.")), (NULL));
    return FALSE;
  }
no_samples:
  {
    gst_qtdemux_stbl_free (stream);
    if (!qtdemux->fragmented) {

      GST_WARNING_OBJECT (qtdemux, "stream has no samples");
      return FALSE;
    } else {

      return TRUE;
    }
  }
}
