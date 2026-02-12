static inline int call_commit_handler(struct net_device *	dev)
{
	if((netif_running(dev)) &&
	   (dev->wireless_handlers->standard[0] != NULL)) {

		return dev->wireless_handlers->standard[0](dev, NULL,
							   NULL, NULL);
	} else
		return 0;
}
