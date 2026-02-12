static inline struct iw_statistics *get_wireless_stats(struct net_device *dev)
{

	if((dev->wireless_handlers != NULL) &&
	   (dev->wireless_handlers->get_wireless_stats != NULL))
		return dev->wireless_handlers->get_wireless_stats(dev);


	return (dev->get_wireless_stats ?
		dev->get_wireless_stats(dev) :
		(struct iw_statistics *) NULL);
}
