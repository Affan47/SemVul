dib0700_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	struct dib0700_state *st = adap->dev->priv;
	int ret;

	if ((onoff != 0) && (st->fw_version >= 0x10201)) {


		ret = dib0700_set_usb_xfer_len(adap->dev,
			st->nb_packet_buffer_size);
		if (ret < 0) {
			deb_info("can not set the USB xfer len\n");
			return ret;
		}
	}

	mutex_lock(&adap->dev->usb_mutex);

	st->buf[0] = REQUEST_ENABLE_VIDEO;


	st->buf[1] = (onoff << 4) | 0x00;

	if (st->disable_streaming_master_mode == 1)
		st->buf[2] = 0x00;
	else
		st->buf[2] = 0x01 << 4;

	st->buf[3] = 0x00;

	deb_info("modifying (%d) streaming state for %d\n", onoff, adap->id);

	st->channel_state &= ~0x3;
	if ((adap->fe_adap[0].stream.props.endpoint != 2)
			&& (adap->fe_adap[0].stream.props.endpoint != 3)) {
		deb_info("the endpoint number (%i) is not correct, use the adapter id instead", adap->fe_adap[0].stream.props.endpoint);
		if (onoff)
			st->channel_state |=	1 << (adap->id);
		else
			st->channel_state |=	1 << ~(adap->id);
	} else {
		if (onoff)
			st->channel_state |=	1 << (adap->fe_adap[0].stream.props.endpoint-2);
		else
			st->channel_state |=	1 << (3-adap->fe_adap[0].stream.props.endpoint);
	}

	st->buf[2] |= st->channel_state;

	deb_info("data for streaming: %x %x\n", st->buf[1], st->buf[2]);

	ret = dib0700_ctrl_wr(adap->dev, st->buf, 4);
	mutex_unlock(&adap->dev->usb_mutex);

	return ret;
}
