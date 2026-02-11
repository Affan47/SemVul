dibusb_pid_filter_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	if (adap->priv != NULL) {
		struct dibusb_state *st = adap->priv;
		if (st->ops.pid_parse != NULL)
			if (st->ops.pid_parse(adap->fe_adap[0].fe, onoff) < 0)
				err("could not handle pid_parser");
	}
	return 0;
}
