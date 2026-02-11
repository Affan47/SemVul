commGetData (int channel, char *buffer, int buflen)
{
   if (channel<0||channel>=N_BUFFERS)
      return -1;

   if (channel==COMM_FFTCH)
   {
      if (psk31fft->has_new_data())
      {
         int len;
         psk31fft->get_parameters(&len, NULL, NULL);
         if(buflen<(int)(len*sizeof(float)))
         {
            fprintf(stderr,"no space in buffer for FFT data\n");
            return 0;
         }
      psk31fft->get_abs_data((float *)buffer, 0, len, 1);
      #if 0
      for(int i=0; i<1024; i++)
            fprintf(stderr,"%d ",((float *)buffer)[i]);
      #endif
      return len;
      }
      else
         return 0;
   }
   else
   {
      return read_buffer(channel, buffer, buflen);
   }
}
