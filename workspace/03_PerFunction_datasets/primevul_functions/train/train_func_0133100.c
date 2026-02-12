__common_section_checks (GstMpegtsSection * section, guint min_size,
    GstMpegtsParseFunc parsefunc, GDestroyNotify destroynotify)
{
  gpointer res;


  if (section->section_length < min_size) {
    GST_WARNING
        ("PID:0x%04x table_id:0x%02x, section too small (Got %d, need at least %d)",
        section->pid, section->table_id, section->section_length, min_size);
    return NULL;
  }


  if (!section->short_section
      && (_calc_crc32 (section->data, section->section_length) != 0)) {
    GST_WARNING ("PID:0x%04x table_id:0x%02x, Bad CRC on section", section->pid,
        section->table_id);
    return NULL;
  }


  res = parsefunc (section);
  if (res == NULL)
    GST_WARNING ("PID:0x%04x table_id:0x%02x, Failed to parse section",
        section->pid, section->table_id);
  else
    section->destroy_parsed = destroynotify;
  return res;
}
