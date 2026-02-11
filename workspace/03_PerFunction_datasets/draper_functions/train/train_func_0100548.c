fossil_system(const char *zOrigCmd){
  int rc;
#if defined(_WIN32)


  char *zNewCmd = mprintf("\"%s\"", zOrigCmd);
  wchar_t *zUnicode = fossil_utf8_to_unicode(zNewCmd);
  if( g.fSystemTrace ) {
    fossil_trace("SYSTEM: %s\n", zNewCmd);
  }
  rc = _wsystem(zUnicode);
  fossil_unicode_free(zUnicode);
  free(zNewCmd);
#else


  if( g.fSystemTrace ) fprintf(stderr, "SYSTEM: %s\n", zOrigCmd);
  rc = system(zOrigCmd);
#endif
  return rc;
}
