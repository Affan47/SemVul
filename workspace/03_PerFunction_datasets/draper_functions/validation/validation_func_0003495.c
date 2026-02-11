compat_write_data(int fd, unsigned char data)
{
   int len=0;


   if (wait_status(fd, PARPORT_STATUS_BUSY, 0, PP_DEVICE_TIMEOUT))
   {
      BUG("compat_write_data transfer stalled\n");
      goto bugout;
   }

   ioctl(fd, PPWDATA, &data);
   wait(PP_SETUP_TIMEOUT);


   frob_control(fd, PARPORT_CONTROL_STROBE, 0);


   if (wait_status(fd, PARPORT_STATUS_BUSY, PARPORT_STATUS_BUSY, PP_SIGNAL_TIMEOUT))
   {
      BUG("compat_write_data transfer stalled\n");
      goto bugout;
   }


   frob_control(fd, PARPORT_CONTROL_STROBE, PARPORT_CONTROL_STROBE);

   len = 1;

bugout:
   return len;
}
