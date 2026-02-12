SkipDataBlocks(gif_source_ptr sinfo)

{
  U_CHAR buf[256];

  while (GetDataBlock(sinfo, buf) > 0)
    ;
}
