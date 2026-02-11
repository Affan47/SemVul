printTimersToStderr()
{
  fprintf(stderr,"Performance report -=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
  fprintf(stderr," FUNCTION                     TIME  IN  MICROSECONDS  SAMPLES!!\n");
  fprintf(stderr,"                              min/avg/max   last      count    \n");
  unsigned int i=0;
  for (i=0; i<TOTAL_TIMERS; i++)
   {
     fprintf(stderr," %s , %u/%u/%u , LAST %u , SAMPLES %u \n",timerIDDescription[i],GetMinimumTimer(i),GetAverageTimer(i),GetMaximumTimer(i),GetLastTimer(i),GetTimesTimerTimed(i));
   }
  fprintf(stderr,"     -=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

}
