moov_recov_file_parse_mvhd (MoovRecovFile * moovrf)
{
  guint32 fourcc;
  guint32 size;
  if (!read_atom_header (moovrf->file, &fourcc, &size)) {
    return FALSE;
  }

  if (fourcc != FOURCC_mvhd)
    return FALSE;

  moovrf->mvhd_size = size;
  moovrf->mvhd_pos = ftell (moovrf->file) - 8;


  return fseek (moovrf->file, size - 8, SEEK_CUR) == 0;
}
