nv04_dac_save(struct drm_encoder *encoder)
{
	struct nouveau_encoder *nv_encoder = nouveau_encoder(encoder);
	struct drm_device *dev = encoder->dev;

	if (nv_gf4_disp_arch(dev))
		nv_encoder->restore.output = NVReadRAMDAC(dev, 0, NV_PRAMDAC_DACCLK +
							  nv04_dac_output_offset(encoder));
}
