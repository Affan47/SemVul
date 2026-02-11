sanei_umax_pp_parkWait (void)
{
  int status;


  DBG (16, "entering parkWait ...\n");
  do
    {
      usleep (1000);
      CMDSYNC (0x40);
      status = sanei_umax_pp_scannerStatus ();
    }
  while ((status & MOTOR_BIT) == 0x00);
  DBG (16, "parkWait done ...\n");
  return 1;
}
