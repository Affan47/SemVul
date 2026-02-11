max3421_handle_error(struct usb_hcd *hcd, u8 hrsl)
{
	struct spi_device *spi = to_spi_device(hcd->self.controller);
	struct max3421_hcd *max3421_hcd = hcd_to_max3421(hcd);
	u8 result_code = hrsl & MAX3421_HRSL_RESULT_MASK;
	struct urb *urb = max3421_hcd->curr_urb;
	struct max3421_ep *max3421_ep = urb->ep->hcpriv;
	int switch_sndfifo;


	switch_sndfifo = (max3421_ep->pkt_state == PKT_STATE_TRANSFER &&
			  usb_urb_dir_out(urb));

	switch (result_code) {
	case MAX3421_HRSL_OK:
		return;

	case MAX3421_HRSL_WRONGPID:
	case MAX3421_HRSL_BUSY:
	case MAX3421_HRSL_BADREQ:
	case MAX3421_HRSL_UNDEF:
	case MAX3421_HRSL_KERR:
	case MAX3421_HRSL_JERR:


		max3421_hcd->urb_done = hrsl_to_error[result_code];
		dev_dbg(&spi->dev, "%s: unexpected error HRSL=0x%02x",
			__func__, hrsl);
		break;

	case MAX3421_HRSL_TOGERR:
		if (usb_urb_dir_in(urb))
			;
		else {

			int sndtog = (hrsl >> MAX3421_HRSL_SNDTOGRD_BIT) & 1;

			sndtog ^= 1;
			spi_wr8(hcd, MAX3421_REG_HCTL,
				BIT(sndtog + MAX3421_HCTL_SNDTOG0_BIT));
		}

	case MAX3421_HRSL_BADBC:
	case MAX3421_HRSL_PIDERR:
	case MAX3421_HRSL_PKTERR:
	case MAX3421_HRSL_CRCERR:
	case MAX3421_HRSL_BABBLE:
	case MAX3421_HRSL_TIMEOUT:
		if (max3421_ep->retries++ < USB_MAX_RETRIES)

			max3421_slow_retransmit(hcd);
		else {

			max3421_hcd->urb_done = hrsl_to_error[result_code];
			dev_dbg(&spi->dev, "%s: unexpected error HRSL=0x%02x",
				__func__, hrsl);
		}
		break;

	case MAX3421_HRSL_STALL:
		dev_dbg(&spi->dev, "%s: unexpected error HRSL=0x%02x",
			__func__, hrsl);
		max3421_hcd->urb_done = hrsl_to_error[result_code];
		break;

	case MAX3421_HRSL_NAK:


		if (max3421_ep->naks++ < NAK_MAX_FAST_RETRANSMITS) {
			max3421_next_transfer(hcd, 1);
			switch_sndfifo = 0;
		} else
			max3421_slow_retransmit(hcd);
		break;
	}
	if (switch_sndfifo)
		spi_wr8(hcd, MAX3421_REG_SNDBC, 0);
}
