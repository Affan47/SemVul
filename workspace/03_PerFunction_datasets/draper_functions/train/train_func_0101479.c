subrip_wr_init(const char *fname)
{
  time_t gpstime_t;
  struct tm * ptm_gps;

  stnum = 1;

  time_offset = 0;

  prevwpp = NULL;

  if ((opt_gpstime != NULL) && (opt_gpsdate != NULL)) {
    time(&gpstime_t);
    ptm_gps = gmtime(&gpstime_t);
    if (opt_gpstime) {
      sscanf(opt_gpstime, "%2d%2d%2d", &ptm_gps->tm_hour, &ptm_gps->tm_min, &ptm_gps->tm_sec);
    }
    if (opt_gpsdate) {
      sscanf(opt_gpsdate, "%4d%2d%2d", &ptm_gps->tm_year, &ptm_gps->tm_mon, &ptm_gps->tm_mday);


      ptm_gps->tm_year-=1900;
      ptm_gps->tm_mon--;
    }
    gpstime_t = mkgmtime(ptm_gps);
    time_offset = sync_time(gpstime_t, opt_videotime);

  }

  fout = gbfopen(fname, "wb", MYNAME);

}
