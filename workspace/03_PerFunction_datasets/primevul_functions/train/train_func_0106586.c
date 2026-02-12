dev_release (struct inode *inode, struct file *fd)
{
	struct dev_data		*dev = fd->private_data;


	if (dev->gadget_registered) {
		usb_gadget_unregister_driver (&gadgetfs_driver);
		dev->gadget_registered = false;
	}


	kfree (dev->buf);
	dev->buf = NULL;


	spin_lock_irq(&dev->lock);
	dev->state = STATE_DEV_DISABLED;
	spin_unlock_irq(&dev->lock);

	put_dev (dev);
	return 0;
}
