snd_tea575x_read(struct snd_tea575x *tea)
{
	u16 l, rdata;
	u32 data = 0;

	if (tea->ops->read_val)
		return tea->ops->read_val(tea);

	tea->ops->set_direction(tea, 0);
	tea->ops->set_pins(tea, 0);
	udelay(16);

	for (l = 24; l--;) {
		tea->ops->set_pins(tea, TEA575X_CLK);
		udelay(2);
		if (!l)
			tea->tuned = tea->ops->get_pins(tea) & TEA575X_MOST ? 0 : 1;
		tea->ops->set_pins(tea, 0);
		udelay(2);
		data <<= 1;
		rdata = tea->ops->get_pins(tea);
		if (!l)
			tea->stereo = (rdata & TEA575X_MOST) ?  0 : 1;
		if (rdata & TEA575X_DATA)
			data++;
		udelay(2);
	}

	if (tea->mute)
		tea->ops->set_pins(tea, TEA575X_WREN);

	return data;
}
