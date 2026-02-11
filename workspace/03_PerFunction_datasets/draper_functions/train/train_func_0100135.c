output_zchar_to_streams(uint8_t *zchar_src)
{
  TRACE_LOG("Converting zchars from %lx.\n",
    (unsigned long int)(zchar_src - z_mem));

  do
  {
    zchar_src = zchar_to_z_ucs(
        z_ucs_output_buffer,
        Z_UCS_OUTPUT_BUFFER_SIZE,
        zchar_src);

    TRACE_LOG("zchar-src %p, mbstage: %d, currentchar: %d, abbrlevel %d\n",
        zchar_to_z_ucs_src_index[zchar_to_z_ucs_abbreviation_level],
        zchar_to_z_ucs_multibyte_stage[zchar_to_z_ucs_abbreviation_level],
        zchar_to_z_ucs_current_z_char[zchar_to_z_ucs_abbreviation_level],
        zchar_to_z_ucs_abbreviation_level);

    (void)streams_z_ucs_output(z_ucs_output_buffer);
  }
  while (zchar_src == NULL);

  return zchar_src;
}
