_packetize_pat (GstMpegtsSection * section)
{
  GPtrArray *programs;
  guint8 *data;
  gsize length;
  guint i;

  programs = gst_mpegts_section_get_pat (section);

  if (programs == NULL)
    return FALSE;


  length = 12;


  length += programs->len * 4;

  _packetize_common_section (section, length);
  data = section->data + 8;

  for (i = 0; i < programs->len; i++) {
    GstMpegtsPatProgram *program;

    program = g_ptr_array_index (programs, i);


    GST_WRITE_UINT16_BE (data, program->program_number);
    data += 2;


    GST_WRITE_UINT16_BE (data, program->network_or_program_map_PID | 0xE000);
    data += 2;
  }

  g_ptr_array_unref (programs);

  return TRUE;
}
