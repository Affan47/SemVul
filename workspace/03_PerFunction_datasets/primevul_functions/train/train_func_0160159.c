mptctl_event_process(MPT_ADAPTER *ioc, EventNotificationReply_t *pEvReply)
{
	u8 event;

	event = le32_to_cpu(pEvReply->Event) & 0xFF;

	dctlprintk(ioc, printk(MYIOC_s_DEBUG_FMT "%s() called\n",
	    ioc->name, __func__));
	if(async_queue == NULL)
		return 1;


	if (event == 0x21) {
		ioc->aen_event_read_flag=1;
		dctlprintk(ioc, printk(MYIOC_s_DEBUG_FMT "Raised SIGIO to application\n",
		    ioc->name));
		devtverboseprintk(ioc, printk(MYIOC_s_DEBUG_FMT
		    "Raised SIGIO to application\n", ioc->name));
		kill_fasync(&async_queue, SIGIO, POLL_IN);
		return 1;
	 }


	if(ioc->aen_event_read_flag)
		return 1;


	if (ioc->events && (ioc->eventTypes & ( 1 << event))) {
		ioc->aen_event_read_flag=1;
		dctlprintk(ioc, printk(MYIOC_s_DEBUG_FMT
		    "Raised SIGIO to application\n", ioc->name));
		devtverboseprintk(ioc, printk(MYIOC_s_DEBUG_FMT
		    "Raised SIGIO to application\n", ioc->name));
		kill_fasync(&async_queue, SIGIO, POLL_IN);
	}
	return 1;
}
