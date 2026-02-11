u_clearrecords(const userinput * const u)
{
  int ii;
  updatecontext();

  gdata.record = 0;
  gdata.sentrecord = 0;
  gdata.totalsent = 0;
  gdata.totaluptime = 0;

  for (ii=0; ii<NUMBER_TRANSFERLIMITS; ii++)
    {
      gdata.transferlimits[ii].ends = 0;
    }

  u_respond(u,"Cleared transfer record, bandwidth record, total sent, total uptime, and transfer limits");

}
