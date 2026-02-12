static inline int ioctl_export_private(struct net_device *	dev,
				       struct ifreq *		ifr)
{
	struct iwreq *				iwr = (struct iwreq *) ifr;


	if((dev->wireless_handlers->num_private_args == 0) ||
	   (dev->wireless_handlers->private_args == NULL))
		return -EOPNOTSUPP;


	if(iwr->u.data.pointer == NULL)
		return -EFAULT;


	if(iwr->u.data.length < dev->wireless_handlers->num_private_args) {


		iwr->u.data.length = dev->wireless_handlers->num_private_args;
		return -E2BIG;
	}


	iwr->u.data.length = dev->wireless_handlers->num_private_args;


	if (copy_to_user(iwr->u.data.pointer,
			 dev->wireless_handlers->private_args,
			 sizeof(struct iw_priv_args) * iwr->u.data.length))
		return -EFAULT;

	return 0;
}
