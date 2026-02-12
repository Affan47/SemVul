DoExtension(gif_source_ptr sinfo)


{
  int extlabel;


  extlabel = ReadByte(sinfo);
  TRACEMS1(sinfo->cinfo, 1, JTRC_GIF_EXTENSION, extlabel);

  SkipDataBlocks(sinfo);
}
