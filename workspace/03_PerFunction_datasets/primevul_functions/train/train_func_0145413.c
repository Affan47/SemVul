void peak_usb_restart_complete(struct peak_usb_device *dev)
{

	dev->can.state = CAN_STATE_ERROR_ACTIVE;


	netif_wake_queue(dev->netdev);
}
