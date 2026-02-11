ndelay(int time)
{
   long l;

   l = ticker;
   do {
      releasetimeslice();
   }  while (ticker - l > time);
}
