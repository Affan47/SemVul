gst_mpegts_demux_is_PMT (GstMpegTSDemux * demux, guint16 PID)
{
  GstMpegTSStream *stream;
  GstMpegTSPAT *PAT;
  gint i;


  stream = demux->streams[PID_PROGRAM_ASSOCIATION_TABLE];
  if (stream == NULL || stream->PAT.entries == NULL)
    return FALSE;

  PAT = &stream->PAT;

  for (i = 0; i < PAT->entries->len; i++) {
    GstMpegTSPATEntry *entry;

    entry = &g_array_index (PAT->entries, GstMpegTSPATEntry, i);
    if (!entry)
      continue;

    if (entry->PID == PID)
      return TRUE;
  }
  return FALSE;
}
