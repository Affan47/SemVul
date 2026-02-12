void wireless_send_event(struct net_device *	dev,
			 unsigned int		cmd,
			 union iwreq_data *	wrqu,
			 char *			extra)
{
	const struct iw_ioctl_description *	descr = NULL;
	int extra_len = 0;
	struct iw_event  *event;
	int event_len;
	int hdr_len;

	unsigned	cmd_index;


	if(cmd <= SIOCIWLAST) {
		cmd_index = cmd - SIOCIWFIRST;
		if(cmd_index < standard_ioctl_num)
			descr = &(standard_ioctl[cmd_index]);
	} else {
		cmd_index = cmd - IWEVFIRST;
		if(cmd_index < standard_event_num)
			descr = &(standard_event[cmd_index]);
	}

	if(descr == NULL) {


	  	printk(KERN_ERR "%s (WE) : Invalid/Unknown Wireless Event (0x%04X)\n",
		       dev->name, cmd);
		return;
	}
#ifdef WE_EVENT_DEBUG
	printk(KERN_DEBUG "%s (WE) : Got event 0x%04X\n",
	       dev->name, cmd);
	printk(KERN_DEBUG "%s (WE) : Header type : %d, Token type : %d, size : %d, token : %d\n", dev->name, descr->header_type, descr->token_type, descr->token_size, descr->max_tokens);
#endif


	if(descr->header_type == IW_HEADER_TYPE_POINT) {

		if(wrqu->data.length > descr->max_tokens) {
		  	printk(KERN_ERR "%s (WE) : Wireless Event too big (%d)\n", dev->name, wrqu->data.length);
			return;
		}
		if(wrqu->data.length < descr->min_tokens) {
		  	printk(KERN_ERR "%s (WE) : Wireless Event too small (%d)\n", dev->name, wrqu->data.length);
			return;
		}

		if(extra != NULL)
			extra_len = wrqu->data.length * descr->token_size;
#ifdef WE_EVENT_DEBUG
		printk(KERN_DEBUG "%s (WE) : Event 0x%04X, tokens %d, extra_len %d\n", dev->name, cmd, wrqu->data.length, extra_len);
#endif
	}


	hdr_len = event_type_size[descr->header_type];
	event_len = hdr_len + extra_len;

#ifdef WE_EVENT_DEBUG
	printk(KERN_DEBUG "%s (WE) : Event 0x%04X, hdr_len %d, event_len %d\n", dev->name, cmd, hdr_len, event_len);
#endif


	event = kmalloc(event_len, GFP_ATOMIC);
	if(event == NULL)
		return;


	event->len = event_len;
	event->cmd = cmd;
	memcpy(&event->u, wrqu, hdr_len - IW_EV_LCP_LEN);
	if(extra != NULL)
		memcpy(((char *) event) + hdr_len, extra, extra_len);

#ifdef WE_EVENT_NETLINK

	rtmsg_iwinfo(dev, (char *) event, event_len);
#endif


	kfree(event);

	return;
}
