af9035_get_rc_config(struct dvb_usb_device *d, struct dvb_usb_rc *rc)
{
	struct state *state = d_to_priv(d);
	int ret;
	u8 tmp;

	ret = af9035_rd_reg(d, state->eeprom_addr + EEPROM_IR_MODE, &tmp);
	if (ret < 0)
		goto err;

	dev_dbg(&d->udev->dev, "%s: ir_mode=%02x\n", __func__, tmp);


	if (tmp == 5) {
		ret = af9035_rd_reg(d, state->eeprom_addr + EEPROM_IR_TYPE,
				&tmp);
		if (ret < 0)
			goto err;

		dev_dbg(&d->udev->dev, "%s: ir_type=%02x\n", __func__, tmp);

		switch (tmp) {
		case 0:
		default:
			rc->allowed_protos = RC_BIT_NEC;
			break;
		case 1:
			rc->allowed_protos = RC_BIT_RC6_MCE;
			break;
		}

		rc->query = af9035_rc_query;
		rc->interval = 500;


		if (!rc->map_name)
			rc->map_name = RC_MAP_EMPTY;
	}

	return 0;

err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);

	return ret;
}
