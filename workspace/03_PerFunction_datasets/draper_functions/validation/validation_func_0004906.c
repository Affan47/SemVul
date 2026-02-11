__my_creat(char *fnam)
{
 int32 fd;
 struct stat sbuf;

 if ((fd = creat(fnam, 0666)) == -1) return(-1);
 if (fstat(fd, &sbuf) == -1)
  {
   __crit_msg("**fatal err[1]: OS file stat operation failed: %s\n",
    strerror(errno));
   __my_exit(5, TRUE);
  }

 if ((S_IFDIR & sbuf.st_mode) == 0) return(fd);


 close(fd);
 return(-1);
}
