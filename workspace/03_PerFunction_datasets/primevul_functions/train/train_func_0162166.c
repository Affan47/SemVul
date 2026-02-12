static void pcan_usb_fd_free(struct peak_usb_device *dev)
{

	if (!dev->prev_siblings && !dev->next_siblings) {
		struct pcan_usb_fd_device *pdev =
			container_of(dev, struct pcan_usb_fd_device, dev);


		kfree(pdev->cmd_buffer_addr);


		kfree(pdev->usb_if);
	}
}
