bool get_next_time(const Time_zone *time_zone, my_time_t *next,
                   my_time_t start, my_time_t time_now,
                   int i_value, interval_type i_type)
{
  DBUG_ENTER("get_next_time");
  DBUG_PRINT("enter", ("start: %lu  now: %lu", (long) start, (long) time_now));

  DBUG_ASSERT(start <= time_now);

  longlong months=0, seconds=0;

  switch (i_type) {
  case INTERVAL_YEAR:
    months= i_value*12;
    break;
  case INTERVAL_QUARTER:

  case INTERVAL_YEAR_MONTH:
  case INTERVAL_MONTH:
    months= i_value;
    break;
  case INTERVAL_WEEK:

  case INTERVAL_DAY:
    seconds= i_value*24*3600;
    break;
  case INTERVAL_DAY_HOUR:
  case INTERVAL_HOUR:
    seconds= i_value*3600;
    break;
  case INTERVAL_DAY_MINUTE:
  case INTERVAL_HOUR_MINUTE:
  case INTERVAL_MINUTE:
    seconds= i_value*60;
    break;
  case INTERVAL_DAY_SECOND:
  case INTERVAL_HOUR_SECOND:
  case INTERVAL_MINUTE_SECOND:
  case INTERVAL_SECOND:
    seconds= i_value;
    break;
  case INTERVAL_DAY_MICROSECOND:
  case INTERVAL_HOUR_MICROSECOND:
  case INTERVAL_MINUTE_MICROSECOND:
  case INTERVAL_SECOND_MICROSECOND:
  case INTERVAL_MICROSECOND:


    DBUG_RETURN(1);
  case INTERVAL_LAST:
    DBUG_ASSERT(0);
  }
  DBUG_PRINT("info", ("seconds: %ld  months: %ld", (long) seconds, (long) months));

  MYSQL_TIME local_start;
  MYSQL_TIME local_now;


  {
    time_zone->gmt_sec_to_TIME(&local_start, start);
    time_zone->gmt_sec_to_TIME(&local_now, time_now);
  }

  INTERVAL interval;
  bzero(&interval, sizeof(interval));
  my_time_t next_time= 0;

  if (seconds)
  {
    longlong seconds_diff;
    long microsec_diff;
    bool negative= calc_time_diff(&local_now, &local_start, 1,
                                  &seconds_diff, &microsec_diff);
    if (!negative)
    {


      interval.second= seconds_diff - seconds_diff % seconds + seconds;
      next_time= add_interval(&local_start, time_zone,
                              INTERVAL_SECOND, interval);
      if (next_time == 0)
        goto done;
    }

    if (next_time <= time_now)
    {


      DBUG_ASSERT(negative || next_time > 0);


      interval.second= seconds;
      do
      {
        next_time= add_interval(&local_start, time_zone,
                                INTERVAL_SECOND, interval);
        if (next_time == 0)
          goto done;
      }
      while (next_time <= time_now);
    }
  }
  else
  {
    long diff_months= ((long) local_now.year - (long) local_start.year)*12 +
                      ((long) local_now.month - (long) local_start.month);


    interval.month= (ulong) (diff_months - diff_months % months);
    next_time= add_interval(&local_start, time_zone,
                            INTERVAL_MONTH, interval);
    if (next_time == 0)
      goto done;

    if (next_time <= time_now)
    {
      interval.month= (ulong) months;
      next_time= add_interval(&local_start, time_zone,
                              INTERVAL_MONTH, interval);
      if (next_time == 0)
        goto done;
    }
  }

  DBUG_ASSERT(time_now < next_time);

  *next= next_time;

done:
  DBUG_PRINT("info", ("next_time: %ld", (long) next_time));
  DBUG_RETURN(next_time == 0);
}
