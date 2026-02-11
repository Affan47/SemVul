ca0132_download_dsp_images(struct hda_codec *codec)
{
	bool dsp_loaded = false;
	const struct dsp_image_seg *dsp_os_image;
	const struct firmware *fw_entry;

	if (request_firmware(&fw_entry, EFX_FILE, codec->card->dev) != 0)
		return false;

	dsp_os_image = (struct dsp_image_seg *)(fw_entry->data);
	if (dspload_image(codec, dsp_os_image, 0, 0, true, 0)) {
		codec_err(codec, "ca0132 DSP load image failed\n");
		goto exit_download;
	}

	dsp_loaded = dspload_wait_loaded(codec);

exit_download:
	release_firmware(fw_entry);

	return dsp_loaded;
}
