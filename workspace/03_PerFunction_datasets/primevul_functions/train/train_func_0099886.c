static int date_to_ISO8601 (time_t value, char *buf, int length) {
   struct tm *tm, tmbuf;
   tm = php_gmtime_r(&value, &tmbuf);
   if (!tm) {
	   return 0;
   }
#if 0
	return strftime (buf, length, "%Y-%m-%dT%H:%M:%SZ", tm);
#else
   return strftime(buf, length, "%Y%m%dT%H:%M:%SZ", tm);
#endif
}
