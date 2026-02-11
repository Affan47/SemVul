eventlist(int fd, char *buff, int buflen, int test, int readstep)
{
   fd_set selSet, readySet;
   struct timeval to;
   int active=0;
   int pending;
   int got=0;

   FD_ZERO(&readySet);
   FD_SET(fd,&readySet);
   FD_SET(fileno(stdin),&readySet);
   to.tv_sec=to.tv_usec=0;

   switch(test) {
      case GPM_B_LEFT:
         printf("\r\nNow please press and release several times\r\n"
	         "the left button of your mouse,"
	         " *** trying not to move it ***\r\n\r\n");
         break;

      case GPM_B_MIDDLE:
         printf("\r\nNow please press and release several times\r\n"
	         "the middle button of your mouse,"
	         " *** trying not to move it ***\r\n\r\n");
         break;

      case 0:
         printf("\r\nNow please move the mouse around, without pressing any\r\n"
	         "button. Move it both quickly and slowly\r\n\r\n");
         break;

      default:
         printf("Unknown test to perform\r\n");
         return -1;
   }

   printf("Press any key when you've done enough\r\n");

   while(1) {
      selSet=readySet;
      if ((pending=select(fd+1,&selSet,NULL,NULL,&to)) < 0) continue;
      if (pending==0 && !active) {
         active++;
         to.tv_sec=10;
         continue;
      }
      if (pending==0) return got;

      if (FD_ISSET(0,&selSet)) {
         getchar();
         if (active) return got;
      }
      if (FD_ISSET(fd,&selSet)) {
         if (active) got+=read(fd,buff+got,readstep);
         else read(fd,buff,buflen);
      }
      if (got>buflen-readstep)
         readstep=buflen-got;
      if (readstep==0)
         got--,readstep++;

      to.tv_sec=30;
   }
}
