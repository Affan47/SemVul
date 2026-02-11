Stat(const char* fname,
                                        cmFileTimeComparison_Type* st)
{
#if defined(CMAKE_BUILD_WITH_CMAKE)

  cmFileTimeComparisonInternal::FileStatsMap::iterator fit =
    this->Files.find(fname);
  if ( fit != this->Files.end() )
    {
    *st = fit->second;
    return true;
    }
#endif

#if !defined(_WIN32) || defined(__CYGWIN__)

  int res = ::stat(fname, st);
  if ( res != 0 )
    {
    return false;
    }
#else


  WIN32_FILE_ATTRIBUTE_DATA fdata;
  if(!GetFileAttributesEx(fname, GetFileExInfoStandard, &fdata))
    {
    return false;
    }


  *st = fdata.ftLastWriteTime;
#endif

#if defined(CMAKE_BUILD_WITH_CMAKE)

  this->Files[fname] = *st;
#endif

  return true;
}
