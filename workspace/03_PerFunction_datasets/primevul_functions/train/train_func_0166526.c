int wireless_process_ioctl(struct ifreq *ifr, unsigned int cmd)
{
	struct net_device *dev;
	iw_handler	handler;


	if ((dev = __dev_get_by_name(ifr->ifr_name)) == NULL)
		return -ENODEV;


	switch(cmd)
	{
		case SIOCGIWSTATS:

			return dev_iwstats(dev, ifr);

		case SIOCGIWPRIV:

			if(dev->wireless_handlers != NULL) {


				return ioctl_export_private(dev, ifr);
			}

		default:


			if (!netif_device_present(dev))
				return -ENODEV;

			handler = get_handler(dev, cmd);
			if(handler != NULL) {

				if(cmd < SIOCIWFIRSTPRIV)
					return ioctl_standard_call(dev,
								   ifr,
								   cmd,
								   handler);
				else
					return ioctl_private_call(dev,
								  ifr,
								  cmd,
								  handler);
			}

			if (dev->do_ioctl) {
				return dev->do_ioctl(dev, ifr, cmd);
			}
			return -EOPNOTSUPP;
	}

	return -EINVAL;
}
