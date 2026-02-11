iw_scan(int			skfd,
	char *			ifname,
	int			we_version,
	wireless_scan_head *	context)
{
  int		delay;


  context->result = NULL;
  context->retry = 0;


  while(1)
    {

      delay = iw_process_scan(skfd, ifname, we_version, context);


      if(delay <= 0)
	break;


      usleep(delay * 1000);
    }


  return(delay);
}
