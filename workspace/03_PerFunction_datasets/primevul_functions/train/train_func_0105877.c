off_t MirrorJob::GetBytesCount()
{
   long long bytes_count=Job::GetBytesCount();
   if(!parent_mirror) {


      bytes_count+=bytes_transferred;
   }
   return bytes_count;
}
