static inline int ioctl_standard_call(struct net_device *	dev,
				      struct ifreq *		ifr,
				      unsigned int		cmd,
				      iw_handler		handler)
{
	struct iwreq *				iwr = (struct iwreq *) ifr;
	const struct iw_ioctl_description *	descr;
	struct iw_request_info			info;
	int					ret = -EINVAL;


	if((cmd - SIOCIWFIRST) >= standard_ioctl_num)
		return -EOPNOTSUPP;
	descr = &(standard_ioctl[cmd - SIOCIWFIRST]);

#ifdef WE_IOCTL_DEBUG
	printk(KERN_DEBUG "%s (WE) : Found standard handler for 0x%04X\n",
	       ifr->ifr_name, cmd);
	printk(KERN_DEBUG "%s (WE) : Header type : %d, Token type : %d, size : %d, token : %d\n", dev->name, descr->header_type, descr->token_type, descr->token_size, descr->max_tokens);
#endif


	info.cmd = cmd;
	info.flags = 0;


	if(descr->header_type != IW_HEADER_TYPE_POINT) {


		ret = handler(dev, &info, &(iwr->u), NULL);

#ifdef WE_SET_EVENT

		if((descr->flags & IW_DESCR_FLAG_EVENT) &&
		   ((ret == 0) || (ret == -EIWCOMMIT)))
			wireless_send_event(dev, cmd, &(iwr->u), NULL);
#endif
	} else {
		char *	extra;
		int	extra_size;
		int	user_length = 0;
		int	err;


		extra_size = descr->max_tokens * descr->token_size;


		if(IW_IS_SET(cmd)) {

			if((iwr->u.data.pointer == NULL) &&
			   (iwr->u.data.length != 0))
				return -EFAULT;

			if(iwr->u.data.length > descr->max_tokens)
				return -E2BIG;
			if(iwr->u.data.length < descr->min_tokens)
				return -EINVAL;
		} else {

			if(iwr->u.data.pointer == NULL)
				return -EFAULT;

			user_length = iwr->u.data.length;


			if((descr->flags & IW_DESCR_FLAG_NOMAX) &&
			   (user_length > descr->max_tokens)) {


				extra_size = user_length * descr->token_size;


			}
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
					     iwr->u.data.length *
					     descr->token_size);
			if (err) {
				kfree(extra);
				return -EFAULT;
			}
#ifdef WE_IOCTL_DEBUG
			printk(KERN_DEBUG "%s (WE) : Got %d bytes\n",
			       dev->name,
			       iwr->u.data.length * descr->token_size);
#endif
		}


		ret = handler(dev, &info, &(iwr->u), extra);


		if (!ret && IW_IS_GET(cmd)) {

			if(user_length < iwr->u.data.length) {
				kfree(extra);
				return -E2BIG;
			}

			err = copy_to_user(iwr->u.data.pointer, extra,
					   iwr->u.data.length *
					   descr->token_size);
			if (err)
				ret =  -EFAULT;
#ifdef WE_IOCTL_DEBUG
			printk(KERN_DEBUG "%s (WE) : Wrote %d bytes\n",
			       dev->name,
			       iwr->u.data.length * descr->token_size);
#endif
		}

#ifdef WE_SET_EVENT

		if((descr->flags & IW_DESCR_FLAG_EVENT) &&
		   ((ret == 0) || (ret == -EIWCOMMIT))) {
			if(descr->flags & IW_DESCR_FLAG_RESTRICT)


				wireless_send_event(dev, cmd, &(iwr->u), NULL);
			else
				wireless_send_event(dev, cmd, &(iwr->u),
						    extra);
		}
#endif


		kfree(extra);
	}


	if(ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);


	return ret;
}
