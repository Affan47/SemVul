stk500_setparm(PROGRAMMER * pgm, unsigned parm, unsigned value)
{
  unsigned char buf[16];
  int tries = 0;

 retry:
  tries++;
  buf[0] = Cmnd_STK_SET_PARAMETER;
  buf[1] = parm;
  buf[2] = value;
  buf[3] = Sync_CRC_EOP;

  stk500_send(pgm, buf, 4);

  if (stk500_recv(pgm, buf, 1) < 0)
    exit(1);
  if (buf[0] == Resp_STK_NOSYNC) {
    if (tries > 33) {
      fprintf(stderr, "\n%s: stk500_setparm(): can't get into sync\n",
              progname);
      return -1;
    }
    if (stk500_getsync(pgm) < 0)
      return -1;
    goto retry;
  }
  else if (buf[0] != Resp_STK_INSYNC) {
    fprintf(stderr,
            "\n%s: stk500_setparm(): (a) protocol error, "
            "expect=0x%02x, resp=0x%02x\n",
            progname, Resp_STK_INSYNC, buf[0]);
    return -2;
  }

  if (stk500_recv(pgm, buf, 1) < 0)
    exit(1);
  if (buf[0] == Resp_STK_OK)
    return 0;

  parm = buf[0];
  if (stk500_recv(pgm, buf, 1) < 0)
    exit(1);
  if (buf[0] == Resp_STK_FAILED) {
    fprintf(stderr,
            "\n%s: stk500_setparm(): parameter 0x%02x failed\n",
            progname, parm);
    return -3;
  }
  else {
    fprintf(stderr,
            "\n%s: stk500_setparm(): (a) protocol error, "
            "expect=0x%02x, resp=0x%02x\n",
            progname, Resp_STK_INSYNC, buf[0]);
    return -3;
  }
}
