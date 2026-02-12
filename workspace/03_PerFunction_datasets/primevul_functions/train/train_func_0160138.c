mptctl_gettargetinfo (MPT_ADAPTER *ioc, unsigned long arg)
{
	struct mpt_ioctl_targetinfo __user *uarg = (void __user *) arg;
	struct mpt_ioctl_targetinfo karg;
	VirtDevice		*vdevice;
	char			*pmem;
	int			*pdata;
	int			numDevices = 0;
	int			lun;
	int			maxWordsLeft;
	int			numBytes;
	u8			port;
	struct scsi_device 	*sdev;

	if (copy_from_user(&karg, uarg, sizeof(struct mpt_ioctl_targetinfo))) {
		printk(KERN_ERR MYNAM "%s@%d::mptctl_gettargetinfo - "
			"Unable to read in mpt_ioctl_targetinfo struct @ %p\n",
				__FILE__, __LINE__, uarg);
		return -EFAULT;
	}

	dctlprintk(ioc, printk(MYIOC_s_DEBUG_FMT "mptctl_gettargetinfo called.\n",
	    ioc->name));


	numBytes = karg.hdr.maxDataSize - sizeof(mpt_ioctl_header);
	maxWordsLeft = numBytes/sizeof(int);
	port = karg.hdr.port;

	if (maxWordsLeft <= 0) {
		printk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo() - no memory available!\n",
			ioc->name, __FILE__, __LINE__);
		return -ENOMEM;
	}


	pmem = kzalloc(numBytes, GFP_KERNEL);
	if (!pmem) {
		printk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo() - no memory available!\n",
			ioc->name, __FILE__, __LINE__);
		return -ENOMEM;
	}
	pdata =  (int *) pmem;


	if (ioc->sh){
		shost_for_each_device(sdev, ioc->sh) {
			if (!maxWordsLeft)
				continue;
			vdevice = sdev->hostdata;
			if (vdevice == NULL || vdevice->vtarget == NULL)
				continue;
			if (vdevice->vtarget->tflags &
			    MPT_TARGET_FLAGS_RAID_COMPONENT)
				continue;
			lun = (vdevice->vtarget->raidVolume) ? 0x80 : vdevice->lun;
			*pdata = (((u8)lun << 16) + (vdevice->vtarget->channel << 8) +
			    (vdevice->vtarget->id ));
			pdata++;
			numDevices++;
			--maxWordsLeft;
		}
	}
	karg.numDevices = numDevices;


	if (copy_to_user((char __user *)arg, &karg,
				sizeof(struct mpt_ioctl_targetinfo))) {
		printk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo - "
			"Unable to write out mpt_ioctl_targetinfo struct @ %p\n",
			ioc->name, __FILE__, __LINE__, uarg);
		kfree(pmem);
		return -EFAULT;
	}


	if (copy_to_user(uarg->targetInfo, pmem, numBytes)) {
		printk(MYIOC_s_ERR_FMT "%s@%d::mptctl_gettargetinfo - "
			"Unable to write out mpt_ioctl_targetinfo struct @ %p\n",
			ioc->name, __FILE__, __LINE__, pdata);
		kfree(pmem);
		return -EFAULT;
	}

	kfree(pmem);

	return 0;
}
