void dump(char *timebuf, const char *text,
          FILE *stream, unsigned char *ptr, size_t size,
          trace tracetype, curl_infotype infotype)
{
  size_t i;
  size_t c;

  unsigned int width=0x10;

  if(tracetype == TRACE_ASCII)

    width = 0x40;

  fprintf(stream, "%s%s, %zd bytes (0x%zx)\n", timebuf, text, size, size);

  for(i=0; i<size; i+= width) {

    fprintf(stream, "%04zx: ", i);

    if(tracetype == TRACE_BIN) {

      for(c = 0; c < width; c++)
        if(i+c < size)
          fprintf(stream, "%02x ", ptr[i+c]);
        else
          fputs("   ", stream);
    }

    for(c = 0; (c < width) && (i+c < size); c++) {

      if ((tracetype == TRACE_ASCII) &&
          (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
        i+=(c+2-width);
        break;
      }
#ifdef CURL_DOES_CONVERSIONS

      if ((tracetype == TRACE_ASCII) &&
          (i+c+1 < size) && ptr[i+c]=='\r' && ptr[i+c+1]=='\n') {
        i+=(c+2-width);
        break;
      }

      fprintf(stream, "%c", convert_char(infotype, ptr[i+c]));
#else
      (void)infotype;
      fprintf(stream, "%c",
              (ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:UNPRINTABLE_CHAR);
#endif

      if ((tracetype == TRACE_ASCII) &&
          (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
        i+=(c+3-width);
        break;
      }
    }
    fputc('\n', stream);
  }
  fflush(stream);
}
