bgav_mkv_simple_tag_dump(bgav_mkv_simple_tag_t * t)
  {
  bgav_dprintf("  SimpleTag\n");
  bgav_dprintf("    TagName:      %s\n", t->TagName);
  bgav_dprintf("    TagLanguage:  %s\n", t->TagLanguage);
  bgav_dprintf("    TagDefault:   %d\n", t->TagDefault);
  bgav_dprintf("    TagString:    %s\n", t->TagString);
  bgav_dprintf("    TagBinaryLen: %d\n", t->TagBinaryLen);
  if(t->TagBinaryLen)
    bgav_hexdump(t->TagBinary, t->TagBinaryLen, 16);
  }
