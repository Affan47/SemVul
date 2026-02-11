ACE_POSIX_Asynch_Transmit_File_Result
  (const ACE_Handler::Proxy_Ptr &handler_proxy,
   ACE_HANDLE socket,
   ACE_HANDLE file,
   ACE_Asynch_Transmit_File::Header_And_Trailer *header_and_trailer,
   size_t bytes_to_write,
   u_long offset,
   u_long offset_high,
   size_t bytes_per_send,
   u_long flags,
   const void *act,
   ACE_HANDLE event,
   int priority,
   int signal_number)
  : ACE_POSIX_Asynch_Result
     (handler_proxy, act, event, offset, offset_high, priority, signal_number),
    socket_ (socket),
    header_and_trailer_ (header_and_trailer),
    bytes_per_send_ (bytes_per_send),
    flags_ (flags)
{
  this->aio_fildes = file;
  this->aio_nbytes = bytes_to_write;
}
