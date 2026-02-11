dst_ca_attach(struct dst_state *dst, struct dvb_adapter *dvb_adapter)
{
	struct dvb_device *dvbdev;

	dprintk(verbose, DST_CA_ERROR, 1, "registering DST-CA device");
	if (dvb_register_device(dvb_adapter, &dvbdev, &dvbdev_ca, dst, DVB_DEVICE_CA) == 0) {
		dst->dst_ca = dvbdev;
		return dst->dst_ca;
	}

	return NULL;
}
