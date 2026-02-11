FileIsFullPath(const char* in_name)
{
  kwsys_stl::string name = in_name;
#if defined(_WIN32) || defined(__CYGWIN__)

  if(name.length() < 2)
    {
    return false;
    }
  if(name[1] == ':')
    {
    return true;
    }
  if(name[0] == '\\')
    {
    return true;
    }
#else

  if(name.length() < 1)
    {
    return false;
    }
#endif
#if !defined(_WIN32)
  if(name[0] == '~')
    {
    return true;
    }
#endif


  if(name[0] == '/')
    {
    return true;
    }
  return false;
}
