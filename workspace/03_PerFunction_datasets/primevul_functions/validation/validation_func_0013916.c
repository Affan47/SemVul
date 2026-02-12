GetDataBlock(gif_source_ptr sinfo, U_CHAR *buf)


{
  int count;

  count = ReadByte(sinfo);
  if (count > 0) {
    if (!ReadOK(sinfo->pub.input_file, buf, count))
      ERREXIT(sinfo->cinfo, JERR_INPUT_EOF);
  }
  return count;
}
