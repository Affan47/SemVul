static inline iw_handler get_handler(struct net_device *dev,
				     unsigned int cmd)
{

	unsigned int	index;


	if(dev->wireless_handlers == NULL)
		return NULL;


	index = cmd - SIOCIWFIRST;
	if(index < dev->wireless_handlers->num_standard)
		return dev->wireless_handlers->standard[index];


	index = cmd - SIOCIWFIRSTPRIV;
	if(index < dev->wireless_handlers->num_private)
		return dev->wireless_handlers->private[index];


	return NULL;
}
