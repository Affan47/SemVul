static mz_bool mz_zip_writer_validate_archive_name(const char *pArchive_name) {


  if (*pArchive_name == '/') return MZ_FALSE;
  while (*pArchive_name) {
    if ((*pArchive_name == '\\') || (*pArchive_name == ':')) return MZ_FALSE;
    pArchive_name++;
  }
  return MZ_TRUE;
}
