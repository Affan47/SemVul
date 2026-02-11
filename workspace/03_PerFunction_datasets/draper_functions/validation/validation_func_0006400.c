tpg_calc_buffer_line(const struct tpg_data *tpg, unsigned y,
				    unsigned field)
{
	y += tpg->compose.top;
	switch (field) {
	case V4L2_FIELD_SEQ_TB:
		if (y & 1)
			return tpg->buf_height / 2 + y / 2;
		return y / 2;
	case V4L2_FIELD_SEQ_BT:
		if (y & 1)
			return y / 2;
		return tpg->buf_height / 2 + y / 2;
	default:
		return y;
	}
}
