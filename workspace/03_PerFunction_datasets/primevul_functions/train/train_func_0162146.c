static int pcan_usb_fd_restart_async(struct peak_usb_device *dev,
				     struct urb *urb, u8 *buf)
{
	u8 *pc = buf;


	pc += pcan_usb_fd_build_restart_cmd(dev, pc);


	memset(pc, 0xff, sizeof(struct pucan_command));
	pc += sizeof(struct pucan_command);


	usb_fill_bulk_urb(urb, dev->udev,
			  usb_sndbulkpipe(dev->udev, PCAN_USBPRO_EP_CMDOUT),
			  buf, pc - buf,
			  pcan_usb_pro_restart_complete, dev);


	return usb_submit_urb(urb, GFP_ATOMIC);
}
