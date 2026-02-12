int stub_tx_loop(void *data)
{
	struct usbip_device *ud = data;
	struct stub_device *sdev = container_of(ud, struct stub_device, ud);

	while (!kthread_should_stop()) {
		if (usbip_event_happened(ud))
			break;


		if (stub_send_ret_submit(sdev) < 0)
			break;

		if (stub_send_ret_unlink(sdev) < 0)
			break;

		wait_event_interruptible(sdev->tx_waitq,
					 (!list_empty(&sdev->priv_tx) ||
					  !list_empty(&sdev->unlink_tx) ||
					  kthread_should_stop()));
	}

	return 0;
}
