static int atusb_channel(struct ieee802154_hw *hw, u8 page, u8 channel)
{
	struct atusb *atusb = hw->priv;
	int ret = -ENOTSUPP;

	if (atusb->data) {
		ret = atusb->data->set_channel(hw, page, channel);

		msleep(atusb->data->t_channel_switch);
	}

	return ret;
}
