carl9170_usb_submit_cmd_urb(struct ar9170 *ar)
{
	struct urb *urb;
	int err;

	if (atomic_inc_return(&ar->tx_cmd_urbs) != 1) {
		atomic_dec(&ar->tx_cmd_urbs);
		return 0;
	}

	urb = usb_get_from_anchor(&ar->tx_cmd);
	if (!urb) {
		atomic_dec(&ar->tx_cmd_urbs);
		return 0;
	}

	usb_anchor_urb(urb, &ar->tx_anch);
	err = usb_submit_urb(urb, GFP_ATOMIC);
	if (unlikely(err)) {
		usb_unanchor_urb(urb);
		atomic_dec(&ar->tx_cmd_urbs);
	}
	usb_free_urb(urb);

	return err;
}
