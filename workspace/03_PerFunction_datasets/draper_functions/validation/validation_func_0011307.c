epoch2isotime (gnupg_isotime_t timebuf, time_t atime)
{
  if (atime < 0)
    *timebuf = 0;
  else
    {
      struct tm *tp;
#ifdef HAVE_GMTIME_R
      struct tm tmbuf;

      tp = gmtime_r (&atime, &tmbuf);
#else
      tp = gmtime (&atime);
#endif
      snprintf (timebuf, 16, "%04d%02d%02dT%02d%02d%02d",
                1900 + tp->tm_year, tp->tm_mon+1, tp->tm_mday,
                tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
}
