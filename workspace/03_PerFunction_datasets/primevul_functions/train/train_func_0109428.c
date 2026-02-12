static int readOHDRHeaderMessageNIL(struct READER *reader, int length) {

  if (fseek(reader->fhd, length, SEEK_CUR) < 0)
    return errno;

  return MYSOFA_OK;
}
