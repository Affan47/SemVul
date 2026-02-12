static int dvbv5_set_delivery_system(struct dvb_frontend *fe,
				     u32 desired_system)
{
	int ncaps;
	u32 delsys = SYS_UNDEFINED;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	enum dvbv3_emulation_type type;


	if (desired_system == SYS_UNDEFINED)
		desired_system = fe->ops.delsys[0];


	ncaps = 0;
	while (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) {
		if (fe->ops.delsys[ncaps] == desired_system) {
			c->delivery_system = desired_system;
			dev_dbg(fe->dvb->device,
					"%s: Changing delivery system to %d\n",
					__func__, desired_system);
			return 0;
		}
		ncaps++;
	}


	if (!is_dvbv3_delsys(desired_system)) {
		dev_dbg(fe->dvb->device,
			"%s: Delivery system %d not supported.\n",
			__func__, desired_system);
		return -EINVAL;
	}

	type = dvbv3_type(desired_system);


	ncaps = 0;
	while (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) {
		if (dvbv3_type(fe->ops.delsys[ncaps]) == type)
			delsys = fe->ops.delsys[ncaps];
		ncaps++;
	}


	if (delsys == SYS_UNDEFINED) {
		dev_dbg(fe->dvb->device,
			"%s: Delivery system %d not supported on emulation mode.\n",
			__func__, desired_system);
		return -EINVAL;
	}

	dev_dbg(fe->dvb->device,
		"%s: Using delivery system %d emulated as if it were %d\n",
		__func__, delsys, desired_system);

	return emulate_delivery_system(fe, desired_system);
}
