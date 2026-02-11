cherryview_init_gt_powersave(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 val;

	cherryview_setup_pctx(dev);

	mutex_lock(&dev_priv->rps.hw_lock);

	mutex_lock(&dev_priv->sb_lock);
	val = vlv_cck_read(dev_priv, CCK_FUSE_REG);
	mutex_unlock(&dev_priv->sb_lock);

	switch ((val >> 2) & 0x7) {
	case 3:
		dev_priv->mem_freq = 2000;
		break;
	default:
		dev_priv->mem_freq = 1600;
		break;
	}
	DRM_DEBUG_DRIVER("DDR speed: %d MHz\n", dev_priv->mem_freq);

	dev_priv->rps.max_freq = cherryview_rps_max_freq(dev_priv);
	dev_priv->rps.rp0_freq = dev_priv->rps.max_freq;
	DRM_DEBUG_DRIVER("max GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, dev_priv->rps.max_freq),
			 dev_priv->rps.max_freq);

	dev_priv->rps.efficient_freq = cherryview_rps_rpe_freq(dev_priv);
	DRM_DEBUG_DRIVER("RPe GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, dev_priv->rps.efficient_freq),
			 dev_priv->rps.efficient_freq);

	dev_priv->rps.rp1_freq = cherryview_rps_guar_freq(dev_priv);
	DRM_DEBUG_DRIVER("RP1(Guar) GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, dev_priv->rps.rp1_freq),
			 dev_priv->rps.rp1_freq);


	dev_priv->rps.min_freq = dev_priv->rps.efficient_freq;
	DRM_DEBUG_DRIVER("min GPU freq: %d MHz (%u)\n",
			 intel_gpu_freq(dev_priv, dev_priv->rps.min_freq),
			 dev_priv->rps.min_freq);

	WARN_ONCE((dev_priv->rps.max_freq |
		   dev_priv->rps.efficient_freq |
		   dev_priv->rps.rp1_freq |
		   dev_priv->rps.min_freq) & 1,
		  "Odd GPU freq values\n");

	dev_priv->rps.idle_freq = dev_priv->rps.min_freq;


	if (dev_priv->rps.max_freq_softlimit == 0)
		dev_priv->rps.max_freq_softlimit = dev_priv->rps.max_freq;

	if (dev_priv->rps.min_freq_softlimit == 0)
		dev_priv->rps.min_freq_softlimit = dev_priv->rps.min_freq;

	mutex_unlock(&dev_priv->rps.hw_lock);
}
