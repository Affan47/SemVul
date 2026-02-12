static int readOHDRHeaderMessageFilterPipeline(struct READER *reader) {
  int filterversion, filters;

  filterversion = fgetc(reader->fhd);
  filters = fgetc(reader->fhd);

  if (filterversion < 0 || filters < 0)
    return MYSOFA_READ_ERROR;

  if (filters > 32) {

    mylog("object OHDR filter pipeline message has too many filters: %d\n",
          filters);
    return MYSOFA_INVALID_FORMAT;

  }

  switch (filterversion) {
  case 1:
    return readOHDRHeaderMessageFilterPipelineV1(reader, filters);
  case 2:
    return readOHDRHeaderMessageFilterPipelineV2(reader, filters);
  default:

    mylog(
        "object OHDR filter pipeline message must have version 1 or 2 not %d\n",
        filterversion);
    return MYSOFA_INVALID_FORMAT;

  }
}
