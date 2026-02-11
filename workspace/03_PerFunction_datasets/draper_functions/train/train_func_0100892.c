ACE_SSL_Asynch_Write_Stream_Result
  (ACE_Handler &       handler,
   ACE_HANDLE          handle,
   ACE_Message_Block & message_block,
   size_t              bytes_to_write,
   const void *        act,
   ACE_HANDLE          event,
   int                 priority,
   int                 signal_number
 )
  : AWS_RESULT (handler.proxy (),
                handle,
                message_block,
                bytes_to_write,
                act,
                event,
                priority,
                signal_number
                )
{
}
