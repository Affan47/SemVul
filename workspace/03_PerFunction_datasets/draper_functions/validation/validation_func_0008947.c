az6027_set_voltage(struct dvb_frontend *fe,
			      enum fe_sec_voltage voltage)
{

	u8 buf;
	struct dvb_usb_adapter *adap = fe->dvb->priv;

	struct i2c_msg i2c_msg = {
		.addr	= 0x99,
		.flags	= 0,
		.buf	= &buf,
		.len	= 1
	};


	switch (voltage) {
	case SEC_VOLTAGE_13:
		buf = 1;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		break;

	case SEC_VOLTAGE_18:
		buf = 2;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		break;

	case SEC_VOLTAGE_OFF:
		buf = 0;
		i2c_transfer(&adap->dev->i2c_adap, &i2c_msg, 1);
		break;

	default:
		return -EINVAL;
	}
	return 0;
}
