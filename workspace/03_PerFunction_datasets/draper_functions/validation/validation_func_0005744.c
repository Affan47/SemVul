PT_SaveCache__Arc(PT_Indexes indexes, const char *filename) {
  FILE *fp = fopen(filename, "wb");

  if (fp != NULL) {
    PT_SaveCache__Arc_t st;
    int ret;
    time_t t = PT_GetTimeIndex(indexes);
    struct tm tm = PT_GetTime(t);


    const char *prefix =
      "2 0 HTTrack Website Copier" "\n"
      "URL IP-address Archive-Date Content-Type Result-code Checksum Location Offset Filename Archive-length"
      "\n" "\n";
    sprintf(st.filename, "httrack_%d.arc", (int) t);
    fprintf(fp,
            "filedesc://%s 0.0.0.0 %04d%02d%02d%02d%02d%02d text/plain 200 - - 0 %s %d"
            "\n" "%s", st.filename, tm.tm_year + 1900, tm.tm_mon + 1,
            tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, st.filename,
            (int) strlen(prefix), prefix);
    st.fp = fp;
    st.indexes = indexes;
    st.t = t;
    ret = PT_EnumCache(indexes, PT_SaveCache__Arc_Fun, (void *) &st);
    fclose(fp);
    if (ret != 0)
      (void) unlink(filename);
    return ret;
  }
  return -1;
}
