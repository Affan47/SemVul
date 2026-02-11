GetTimeSpent()
{
   if(end_time<start_time)
      return 0;
   return TimeDiff(end_time,start_time);
}
