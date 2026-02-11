Do()
{
   int m=STALL;
   if(ch!=NOCHAR)
      return m;

   int oldfl=fcntl(fd,F_GETFL);
   if(!(oldfl&O_NONBLOCK))
      fcntl(fd,F_SETFL,oldfl|O_NONBLOCK);

   unsigned char c;
   int res=read(fd,&c,1);
   if(res==-1 && errno==EAGAIN)
      Block(fd,POLLIN);
   else if(res==-1 && errno==EINTR)
      m=MOVED;
   else if(res>0)
   {
      ch=c;
      m=MOVED;
   }
   else
   {
      ch=EOFCHAR;
      m=MOVED;
   }

   if(!(oldfl&O_NONBLOCK))
      fcntl(fd,F_SETFL,oldfl);

   if(res==-1 && ch==EOFCHAR)
      fprintf(stderr,"read(%d): %s\n",fd,strerror(errno));

   return m;
}
