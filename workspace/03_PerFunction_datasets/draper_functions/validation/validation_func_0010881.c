ppp_recv_config (int unit,int mru,u_int32_t asyncmap,int pcomp,int accomp)
{
	u_int x;
	int err;


    if (!still_ppp(unit))
      return;


	if (ioctl(lns[unit].fd, PPPIOCSMRU, (caddr_t) &mru) < 0)
		syslog(LOG_ERR, "ioctl(PPPIOCSMRU): %m");

	x = get_flags(unit,&err);
	if(err)
		return;
	x = accomp ? x & ~SC_REJ_COMP_AC : x | SC_REJ_COMP_AC;
	set_flags (x,unit);
}
