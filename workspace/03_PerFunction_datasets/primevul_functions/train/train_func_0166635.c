static inline int ioctl_private_call(struct net_device *	dev,
				     struct ifreq *		ifr,
				     unsigned int		cmd,
				     iw_handler		handler)
{
	struct iwreq *			iwr = (struct iwreq *) ifr;
	const struct iw_priv_args *	descr = NULL;
	struct iw_request_info		info;
	int				extra_size = 0;
	int				i;
	int				ret = -EINVAL;


	for(i = 0; i < dev->wireless_handlers->num_private_args; i++)
		if(cmd == dev->wireless_handlers->private_args[i].cmd) {
			descr = &(dev->wireless_handlers->private_args[i]);
			break;
		}

#ifdef WE_IOCTL_DEBUG
	printk(KERN_DEBUG "%s (WE) : Found private handler for 0x%04X\n",
	       ifr->ifr_name, cmd);
	if(descr) {
		printk(KERN_DEBUG "%s (WE) : Name %s, set %X, get %X\n",
		       dev->name, descr->name,
		       descr->set_args, descr->get_args);
	}
#endif


	if(descr != NULL) {
		if(IW_IS_SET(cmd)) {
			int	offset = 0;

			if(descr->name[0] == '\0')

				offset = sizeof(__u32);


			extra_size = get_priv_size(descr->set_args);


			if((descr->set_args & IW_PRIV_SIZE_FIXED) &&
			   ((extra_size + offset) <= IFNAMSIZ))
				extra_size = 0;
		} else {

			extra_size = get_priv_size(descr->get_args);


			if((descr->get_args & IW_PRIV_SIZE_FIXED) &&
			   (extra_size <= IFNAMSIZ))
				extra_size = 0;
		}
	}


	info.cmd = cmd;
	info.flags = 0;


	if(extra_size == 0) {

		ret = handler(dev, &info, &(iwr->u), (char *) &(iwr->u));
	} else {
		char *	extra;
		int	err;


		if(IW_IS_SET(cmd)) {

			if((iwr->u.data.pointer == NULL) &&
			   (iwr->u.data.length != 0))
				return -EFAULT;


			if(iwr->u.data.length > (descr->set_args &
						 IW_PRIV_SIZE_MASK))
				return -E2BIG;
		} else {

			if(iwr->u.data.pointer == NULL)
				return -EFAULT;
		}

#ifdef WE_IOCTL_DEBUG
		printk(KERN_DEBUG "%s (WE) : Malloc %d bytes\n",
		       dev->name, extra_size);
#endif


		extra = kmalloc(extra_size, GFP_KERNEL);
		if (extra == NULL) {
			return -ENOMEM;
		}


		if(IW_IS_SET(cmd) && (iwr->u.data.length != 0)) {
			err = copy_from_user(extra, iwr->u.data.pointer,
					     extra_size);
			if (err) {
				kfree(extra);
				return -EFAULT;
			}
#ifdef WE_IOCTL_DEBUG
			printk(KERN_DEBUG "%s (WE) : Got %d elem\n",
			       dev->name, iwr->u.data.length);
#endif
		}


		ret = handler(dev, &info, &(iwr->u), extra);


		if (!ret && IW_IS_GET(cmd)) {


			if (!(descr->get_args & IW_PRIV_SIZE_FIXED)) {
				extra_size = adjust_priv_size(descr->get_args,
							      &(iwr->u));
			}

			err = copy_to_user(iwr->u.data.pointer, extra,
					   extra_size);
			if (err)
				ret =  -EFAULT;
#ifdef WE_IOCTL_DEBUG
			printk(KERN_DEBUG "%s (WE) : Wrote %d elem\n",
			       dev->name, iwr->u.data.length);
#endif
		}


		kfree(extra);
	}


	if(ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);

	return ret;
}
