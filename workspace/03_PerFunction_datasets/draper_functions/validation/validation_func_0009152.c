em28xx_init_usb_xfer(struct em28xx *dev, enum em28xx_mode mode,
			 int xfer_bulk, int num_bufs, int max_pkt_size,
		    int packet_multiplier,
		    int (*urb_data_copy)(struct em28xx *dev, struct urb *urb))
{
	struct em28xx_dmaqueue *dma_q = &dev->vidq;
	struct em28xx_dmaqueue *vbi_dma_q = &dev->vbiq;
	struct em28xx_usb_bufs *usb_bufs;
	int i;
	int rc;
	int alloc;

	em28xx_isocdbg("em28xx: called em28xx_init_usb_xfer in mode %d\n",
		       mode);

	dev->usb_ctl.urb_data_copy = urb_data_copy;

	if (mode == EM28XX_DIGITAL_MODE) {
		usb_bufs = &dev->usb_ctl.digital_bufs;

		alloc = 0;
	} else {
		usb_bufs = &dev->usb_ctl.analog_bufs;
		alloc = 1;
	}

	if (alloc) {
		rc = em28xx_alloc_urbs(dev, mode, xfer_bulk, num_bufs,
				       max_pkt_size, packet_multiplier);
		if (rc)
			return rc;
	}

	if (xfer_bulk) {
		rc = usb_clear_halt(dev->udev, usb_bufs->urb[0]->pipe);
		if (rc < 0) {
			em28xx_err("failed to clear USB bulk endpoint stall/halt condition (error=%i)\n",
				   rc);
			em28xx_uninit_usb_xfer(dev, mode);
			return rc;
		}
	}

	init_waitqueue_head(&dma_q->wq);
	init_waitqueue_head(&vbi_dma_q->wq);

	em28xx_capture_start(dev, 1);


	for (i = 0; i < usb_bufs->num_bufs; i++) {
		rc = usb_submit_urb(usb_bufs->urb[i], GFP_ATOMIC);
		if (rc) {
			em28xx_err("submit of urb %i failed (error=%i)\n", i,
				   rc);
			em28xx_uninit_usb_xfer(dev, mode);
			return rc;
		}
	}

	return 0;
}
