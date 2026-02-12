static int dvbv3_set_delivery_system(struct dvb_frontend *fe)
{
	int ncaps;
	u32 delsys = SYS_UNDEFINED;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;


	if (c->delivery_system == SYS_UNDEFINED)
		c->delivery_system = fe->ops.delsys[0];


	if (is_dvbv3_delsys(c->delivery_system)) {
		dev_dbg(fe->dvb->device,
				"%s: Using delivery system to %d\n",
				__func__, c->delivery_system);
		return 0;
	}


	ncaps = 0;
	while (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) {
		if (dvbv3_type(fe->ops.delsys[ncaps]) != DVBV3_UNKNOWN) {
			delsys = fe->ops.delsys[ncaps];
			break;
		}
		ncaps++;
	}
	if (delsys == SYS_UNDEFINED) {
		dev_dbg(fe->dvb->device,
			"%s: Couldn't find a delivery system that works with FE_SET_FRONTEND\n",
			__func__);
		return -EINVAL;
	}
	return emulate_delivery_system(fe, delsys);
}
