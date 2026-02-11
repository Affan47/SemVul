nvidia_gpio_setsda(void *data, int state)
{
	struct nvidia_i2c_chan *chan = data;
	struct nvidia_par *par = chan->par;
	u32 val;

	val = NVReadCrtc(par, chan->ddc_base + 1) & 0xf0;

	if (state)
		val |= 0x10;
	else
		val &= ~0x10;

	NVWriteCrtc(par, chan->ddc_base + 1, val | 0x01);
}
