store_attach(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t count)
{
	struct vhci_device *vdev;
	struct socket *socket;
	int sockfd = 0;
	__u32 rhport = 0, devid = 0, speed = 0;
	int err;
	unsigned long flags;


	if (sscanf(buf, "%u %u %u %u", &rhport, &sockfd, &devid, &speed) != 4)
		return -EINVAL;

	usbip_dbg_vhci_sysfs("rhport(%u) sockfd(%u) devid(%u) speed(%u)\n",
			     rhport, sockfd, devid, speed);


	if (valid_args(rhport, speed) < 0)
		return -EINVAL;


	socket = sockfd_lookup(sockfd, &err);
	if (!socket)
		return -EINVAL;


	spin_lock_irqsave(&the_controller->lock, flags);
	vdev = port_to_vdev(rhport);
	spin_lock(&vdev->ud.lock);

	if (vdev->ud.status != VDEV_ST_NULL) {

		spin_unlock(&vdev->ud.lock);
		spin_unlock_irqrestore(&the_controller->lock, flags);

		sockfd_put(socket);

		dev_err(dev, "port %d already used\n", rhport);
		return -EINVAL;
	}

	dev_info(dev,
		 "rhport(%u) sockfd(%d) devid(%u) speed(%u) speed_str(%s)\n",
		 rhport, sockfd, devid, speed, usb_speed_string(speed));

	vdev->devid         = devid;
	vdev->speed         = speed;
	vdev->ud.sockfd     = sockfd;
	vdev->ud.tcp_socket = socket;
	vdev->ud.status     = VDEV_ST_NOTASSIGNED;

	spin_unlock(&vdev->ud.lock);
	spin_unlock_irqrestore(&the_controller->lock, flags);


	vdev->ud.tcp_rx = kthread_get_run(vhci_rx_loop, &vdev->ud, "vhci_rx");
	vdev->ud.tcp_tx = kthread_get_run(vhci_tx_loop, &vdev->ud, "vhci_tx");

	rh_port_connect(rhport, speed);

	return count;
}
