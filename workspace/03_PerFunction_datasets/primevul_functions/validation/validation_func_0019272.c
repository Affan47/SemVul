static int stub_probe(struct usb_device *udev)
{
	struct stub_device *sdev = NULL;
	const char *udev_busid = dev_name(&udev->dev);
	struct bus_id_priv *busid_priv;
	int rc = 0;
	char save_status;

	dev_dbg(&udev->dev, "Enter probe\n");


	sdev = stub_device_alloc(udev);
	if (!sdev)
		return -ENOMEM;


	busid_priv = get_busid_priv(udev_busid);
	if (!busid_priv || (busid_priv->status == STUB_BUSID_REMOV) ||
	    (busid_priv->status == STUB_BUSID_OTHER)) {
		dev_info(&udev->dev,
			"%s is not in match_busid table... skip!\n",
			udev_busid);


		rc = -ENODEV;
		if (!busid_priv)
			goto sdev_free;

		goto call_put_busid_priv;
	}

	if (udev->descriptor.bDeviceClass == USB_CLASS_HUB) {
		dev_dbg(&udev->dev, "%s is a usb hub device... skip!\n",
			 udev_busid);
		rc = -ENODEV;
		goto call_put_busid_priv;
	}

	if (!strcmp(udev->bus->bus_name, "vhci_hcd")) {
		dev_dbg(&udev->dev,
			"%s is attached on vhci_hcd... skip!\n",
			udev_busid);

		rc = -ENODEV;
		goto call_put_busid_priv;
	}


	dev_info(&udev->dev,
		"usbip-host: register new device (bus %u dev %u)\n",
		udev->bus->busnum, udev->devnum);

	busid_priv->shutdown_busid = 0;


	dev_set_drvdata(&udev->dev, sdev);

	busid_priv->sdev = sdev;
	busid_priv->udev = udev;

	save_status = busid_priv->status;
	busid_priv->status = STUB_BUSID_ALLOC;


	put_busid_priv(busid_priv);


	rc = usb_hub_claim_port(udev->parent, udev->portnum,
			(struct usb_dev_state *) udev);
	if (rc) {
		dev_dbg(&udev->dev, "unable to claim port\n");
		goto err_port;
	}

	return 0;

err_port:
	dev_set_drvdata(&udev->dev, NULL);
	usb_put_dev(udev);


	spin_lock(&busid_priv->busid_lock);
	busid_priv->sdev = NULL;
	busid_priv->status = save_status;
	spin_unlock(&busid_priv->busid_lock);

	goto sdev_free;

call_put_busid_priv:

	put_busid_priv(busid_priv);

sdev_free:
	stub_device_free(sdev);

	return rc;
}
