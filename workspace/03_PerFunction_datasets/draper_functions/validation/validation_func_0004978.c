psb_2d_wait_available(struct drm_psb_private *dev_priv,
			  unsigned size)
{
	uint32_t avail = PSB_RSGX32(PSB_CR_2D_SOCIF);
	unsigned long t = jiffies + HZ;

	while (avail < size) {
		avail = PSB_RSGX32(PSB_CR_2D_SOCIF);
		if (time_after(jiffies, t)) {
			psb_spank(dev_priv);
			return -EIO;
		}
	}
	return 0;
}
