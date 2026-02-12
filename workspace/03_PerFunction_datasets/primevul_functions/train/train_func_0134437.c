static void read_bulk_callback(struct urb *urb)
{
	struct hso_net *odev = urb->context;
	struct net_device *net;
	int result;
	unsigned long flags;
	int status = urb->status;


	if (status) {
		handle_usb_error(status, __func__, odev->parent);
		return;
	}


	if (!odev || !test_bit(HSO_NET_RUNNING, &odev->flags)) {
		hso_dbg(0x1, "BULK IN callback but driver is not active!\n");
		return;
	}
	usb_mark_last_busy(urb->dev);

	net = odev->net;

	if (!netif_device_present(net)) {

		return;
	}

	if (odev->parent->port_spec & HSO_INFO_CRC_BUG)
		fix_crc_bug(urb, odev->in_endp->wMaxPacketSize);


	if (urb->actual_length) {


		spin_lock_irqsave(&odev->net_lock, flags);
		packetizeRx(odev, urb->transfer_buffer, urb->actual_length,
			    (urb->transfer_buffer_length >
			     urb->actual_length) ? 1 : 0);
		spin_unlock_irqrestore(&odev->net_lock, flags);
	}


	usb_fill_bulk_urb(urb,
			  odev->parent->usb,
			  usb_rcvbulkpipe(odev->parent->usb,
					  odev->in_endp->
					  bEndpointAddress & 0x7F),
			  urb->transfer_buffer, MUX_BULK_RX_BUF_SIZE,
			  read_bulk_callback, odev);


	result = usb_submit_urb(urb, GFP_ATOMIC);
	if (result)
		dev_warn(&odev->parent->interface->dev,
			 "%s failed submit mux_bulk_rx_urb %d\n", __func__,
			 result);
}
