int iw_handler_set_spy(struct net_device *	dev,
		       struct iw_request_info *	info,
		       union iwreq_data *	wrqu,
		       char *			extra)
{
	struct iw_spy_data *	spydata = get_spydata(dev);
	struct sockaddr *	address = (struct sockaddr *) extra;

	if(!dev->wireless_data)

		printk(KERN_DEBUG "%s (WE) : Driver using old/buggy spy support, please fix driver !\n",
		       dev->name);

	if(!spydata)
		return -EOPNOTSUPP;


	spydata->spy_number = 0;


	wmb();


	if(wrqu->data.length > 0) {
		int i;


		for(i = 0; i < wrqu->data.length; i++)
			memcpy(spydata->spy_address[i], address[i].sa_data,
			       ETH_ALEN);

		memset(spydata->spy_stat, 0,
		       sizeof(struct iw_quality) * IW_MAX_SPY);

#ifdef WE_SPY_DEBUG
		printk(KERN_DEBUG "iw_handler_set_spy() :  offset %ld, spydata %p, num %d\n", dev->wireless_handlers->spy_offset, spydata, wrqu->data.length);
		for (i = 0; i < wrqu->data.length; i++)
			printk(KERN_DEBUG
			       "%02X:%02X:%02X:%02X:%02X:%02X \n",
			       spydata->spy_address[i][0],
			       spydata->spy_address[i][1],
			       spydata->spy_address[i][2],
			       spydata->spy_address[i][3],
			       spydata->spy_address[i][4],
			       spydata->spy_address[i][5]);
#endif
	}


	wmb();


	spydata->spy_number = wrqu->data.length;

	return 0;
}
