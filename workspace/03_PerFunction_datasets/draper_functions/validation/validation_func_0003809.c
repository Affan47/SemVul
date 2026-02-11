cifaddr (int unit, int our_adr, int his_adr)
{
    struct rtentry rt;


	if (!devroute)
		return 1;

    memset (&rt, '\0', sizeof (rt));

    SET_SA_FAMILY (rt.rt_dst,     AF_INET);
    SET_SA_FAMILY (rt.rt_gateway, AF_INET);
	SET_SA_FAMILY (rt.rt_genmask, AF_INET);
    rt.rt_dev = lns[unit].ifname;

	if (last_net_mask)
		his_adr &= last_net_mask;
    ((struct sockaddr_in *) &rt.rt_gateway)->sin_addr.s_addr = 0;
    ((struct sockaddr_in *) &rt.rt_dst)->sin_addr.s_addr     = his_adr;
	((struct sockaddr_in *) &rt.rt_genmask)->sin_addr.s_addr = last_net_mask;
	rt.rt_flags = RTF_UP;
	if (last_net_mask == 0)
		rt.rt_flags |= RTF_HOST;

	if (ioctl(sockfd, SIOCDELRT, &rt) < 0 && errno != ESRCH) {
		if (still_ppp(unit)) {
			syslog (LOG_ERR, "ioctl(SIOCDELRT) device route: %m");
			return (0);
		}
	}
	return 1;
}
