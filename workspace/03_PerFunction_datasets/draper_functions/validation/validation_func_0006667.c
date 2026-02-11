wr_fix_record(const waypoint* wpt, int pres_alt, int gnss_alt)
{
  struct tm* tm;

  if (NULL == (tm = gmtime(&wpt->creation_time))) {
    fatal(MYNAME ": bad track timestamp\n");
  }

  if (unknown_alt == pres_alt) {
    pres_alt = 0;
  }
  if (unknown_alt == gnss_alt) {
    gnss_alt = 0;
  }
  gbfprintf(file_out, "B%02u%02u%02u%sA%05d%05d\r\n", tm->tm_hour,
            tm->tm_min, tm->tm_sec, latlon2str(wpt), pres_alt, gnss_alt);
}
