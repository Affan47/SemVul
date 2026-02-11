EXTRACTOR_meta_data_print (void *handle,
			   const char *plugin_name,
			   enum EXTRACTOR_MetaType type,
			   enum EXTRACTOR_MetaFormat format,
			   const char *data_mime_type,
			   const char *data,
			   size_t data_len)
{
#if HAVE_ICONV
  iconv_t cd;
#endif
  char * buf;
  int ret;
  const char *mt;

  if (EXTRACTOR_METAFORMAT_UTF8 != format)
    return 0;
#if HAVE_ICONV
  cd = iconv_open (nl_langinfo(CODESET),
		   "UTF-8");
  if (((iconv_t) -1) == cd)
    {
      LOG_STRERROR ("iconv_open");
      return 1;
    }
  buf = iconv_helper (cd, data, data_len);
  if (NULL == buf)
    {
      LOG_STRERROR ("iconv_helper");
      ret = -1;
    }
  else
    {
      mt = EXTRACTOR_metatype_to_string (type);
      ret = fprintf (handle,
		     "%s - %s\n",
		     (NULL == mt)
		     ? dgettext ("libextractor", gettext_noop ("unknown"))
		     : dgettext ("libextractor", mt),
		     buf);
      free(buf);
    }
  iconv_close(cd);
#else
  ret = fprintf (handle,
		 "%s - %.*s\n",
		 (NULL == mt)
		 ? dgettext ("libextractor", gettext_noop ("unknown"))
		 : dgettext ("libextractor", mt),
		 (int) data_len,
		 data);
#endif
  return (ret < 0) ? 1 : 0;
}
