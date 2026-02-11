channel_clear(struct sh_dmae_chan *sh_dc)
{
	struct sh_dmae_device *shdev = to_sh_dev(sh_dc);
	const struct sh_dmae_channel *chan_pdata = shdev->pdata->channel +
		sh_dc->shdma_chan.id;
	u32 val = shdev->pdata->chclr_bitwise ? 1 << chan_pdata->chclr_bit : 0;

	__raw_writel(val, shdev->chan_reg + chan_pdata->chclr_offset);
}
