static std::string get_dtd_installation_directory()
{


  char ch_fn[MAX_PATH], *p;
  std::string str_fn;

  if (!GetModuleFileName(NULL, ch_fn, MAX_PATH)) return "";

  if ((p = strrchr(ch_fn, '\\')) != NULL)
    * p = '\0';

  p = strrchr(ch_fn, '\\');
  if (p && (_stricmp(p + 1, "bin") == 0 ||
            _stricmp(p + 1, "lib") == 0))
    *p = '\0';

  str_fn = ch_fn;
  str_fn += "\\share\\libofx\\dtd";

  return str_fn;
}
