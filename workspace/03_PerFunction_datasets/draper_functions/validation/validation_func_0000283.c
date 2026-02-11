gribVersion(unsigned char *is, size_t buffersize)
{
  if ( buffersize < 8 )
    Error("Buffer too small (current size %d)!", (int) buffersize);

  return (GRIB_EDITION(is));
}
