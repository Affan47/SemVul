edf_set_startdatetime(int handle, int startdate_year, int startdate_month, int startdate_day,
                                      int starttime_hour, int starttime_minute, int starttime_second)
{
  if(handle<0)
  {
    return(-1);
  }

  if(handle>=EDFLIB_MAXFILES)
  {
    return(-1);
  }

  if(hdrlist[handle]==NULL)
  {
    return(-1);
  }

  if(!(hdrlist[handle]->writemode))
  {
    return(-1);
  }

  if(hdrlist[handle]->datarecords)
  {
    return(-1);
  }

  if((startdate_year<1970) || (startdate_year>3000) ||
     (startdate_month<1)   || (startdate_month>12)  ||
     (startdate_day<1)     || (startdate_day>31)    ||
     (starttime_hour<0)    || (starttime_hour>23)   ||
     (starttime_minute<0)  || (starttime_minute>59) ||
     (starttime_second<0)  || (starttime_second>59))
  {
    return(-1);
  }

  hdrlist[handle]->startdate_year = startdate_year;
  hdrlist[handle]->startdate_month = startdate_month;
  hdrlist[handle]->startdate_day = startdate_day;
  hdrlist[handle]->starttime_hour = starttime_hour;
  hdrlist[handle]->starttime_minute = starttime_minute;
  hdrlist[handle]->starttime_second = starttime_second;

  return(0);
}
