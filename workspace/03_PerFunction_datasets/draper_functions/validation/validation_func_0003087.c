WantSize()
{
   struct stat st;
   st.st_size=NO_SIZE;

   if(stream->fd!=-1)
      fstat(stream->fd,&st);
   else if(stream->full_name)
      stat(stream->full_name,&st);

   if(st.st_size!=NO_SIZE)
      SetSize(st.st_size);
   else
      super::WantSize();
}
