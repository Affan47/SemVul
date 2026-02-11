dspxfr_hci_write(struct hda_codec *codec,
			const struct dsp_image_seg *fls)
{
	int status;
	const u32 *data;
	unsigned int count;

	if (fls == NULL || fls->chip_addr != g_chip_addr_magic_value) {
		codec_dbg(codec, "hci_write invalid params\n");
		return -EINVAL;
	}

	count = fls->count;
	data = (u32 *)(fls->data);
	while (count >= 2) {
		status = chipio_write(codec, data[0], data[1]);
		if (status < 0) {
			codec_dbg(codec, "hci_write chipio failed\n");
			return status;
		}
		count -= 2;
		data  += 2;
	}
	return 0;
}
