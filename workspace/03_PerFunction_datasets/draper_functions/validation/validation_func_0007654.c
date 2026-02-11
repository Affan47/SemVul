p_save_chunk_as_frame(const char *filename,  unsigned char *video_chunk, gint32 video_frame_chunk_size, gint32 header_length)
{
  FILE   *fp;
  char   *dataPtr;
  gint32  dataSize;

  dataSize = video_frame_chunk_size - header_length;
  dataPtr = video_chunk + header_length;

  fp = fopen(filename, "w");
  if (fp)
  {
    fwrite(dataPtr, dataSize, 1, fp);
    fclose(fp);
    return (TRUE);
  }

  printf("ERROR cant write to file:%s\n", filename);
  return (FALSE);
}
