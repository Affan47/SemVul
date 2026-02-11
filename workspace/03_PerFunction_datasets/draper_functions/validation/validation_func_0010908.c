THDiskFile_readString(THFile *self, const char *format, char **str_)
{
  THDiskFile *dfself = (THDiskFile*)(self);
  THArgCheck(dfself->handle != NULL, 1, "attempt to use a closed file");
  THArgCheck(dfself->file.isReadable, 1, "attempt to read in a write-only file");
  THArgCheck((strlen(format) >= 2 ? (format[0] == '*') && (format[1] == 'a' || format[1] == 'l') : 0), 2, "format must be '*a' or '*l'");


#define TBRS_BSZ 1024L

  if(format[1] == 'a')
  {
    char *p = THAlloc(TBRS_BSZ);
    long total = TBRS_BSZ;
    long pos = 0L;

    for (;;)
    {
      if(total-pos == 0)
      {
        total += TBRS_BSZ;
        p = THRealloc(p, total);
      }
      pos += fread(p+pos, 1, total-pos, dfself->handle);
      if (pos < total)
      {
        if(pos == 0L)
        {
          THFree(p);
          dfself->file.hasError = 1;
          if(!dfself->file.isQuiet)
            THError("read error: read 0 blocks instead of 1");

          *str_ = NULL;
          return 0;
        }
        *str_ = p;
        return pos;
      }
    }
  }
  else
  {
    char *p = THAlloc(TBRS_BSZ);
    long total = TBRS_BSZ;
    long pos = 0L;
    long size;

    for (;;)
    {
      if(total-pos <= 1)
      {
        total += TBRS_BSZ;
        p = THRealloc(p, total);
      }
      if (fgets(p+pos, total-pos, dfself->handle) == NULL)
      {
        if(pos == 0L)
        {
          THFree(p);
          dfself->file.hasError = 1;
          if(!dfself->file.isQuiet)
            THError("read error: read 0 blocks instead of 1");

          *str_ = NULL;
          return 0;
        }
        *str_ = p;
        return pos;
      }
      size = strlen(p+pos);
      if (size == 0L || (p+pos)[size-1] != '\n')
      {
        pos += size;
      }
      else
      {
        pos += size-1L;
        *str_ = p;
        return pos;
      }
    }
  }

  *str_ = NULL;
  return 0;
}
