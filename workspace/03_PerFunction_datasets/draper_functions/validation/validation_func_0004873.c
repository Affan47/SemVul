af9005_fe_select_bw(struct dvb_usb_device *d, u32 bw)
{
	u8 temp;
	switch (bw) {
	case 6000000:
		temp = 0;
		break;
	case 7000000:
		temp = 1;
		break;
	case 8000000:
		temp = 2;
		break;
	default:
		err("Invalid bandwidth %d.", bw);
		return -EINVAL;
	}
	return af9005_write_register_bits(d, xd_g_reg_bw, reg_bw_pos,
					  reg_bw_len, temp);
}
