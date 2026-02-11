Lock(int fd,int type)
{
   struct flock	lk;
   lk.l_type=type;
   lk.l_whence=0;
   lk.l_start=0;
   lk.l_len=0;
   int res=fcntl(fd,F_SETLK,&lk);
   if(res==-1 && E_RETRY(errno))
   {
      int retries=5;
      bool echo=true;
      for(int i=0; i<retries; i++)
      {
	 sleep(1);
	 if(echo && write(2,".",1)==-1)
	    echo=false;
	 res=fcntl(fd,F_SETLK,&lk);
	 if(res==0)
	    break;
      }
      if(echo && write(2,"\r",1)==-1)
	 echo=false;
   }
   if(res==-1 && E_LOCK_IGNORE(errno))
      return 0;
   return res;
}
