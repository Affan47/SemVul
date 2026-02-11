gt_max_freq_mhz_store(struct device *kdev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct drm_minor *minor = dev_to_drm_minor(kdev);
	struct drm_device *dev = minor->dev;
	struct drm_i915_private *dev_priv = dev->dev_private;
	u32 val;
	ssize_t ret;

	ret = kstrtou32(buf, 0, &val);
	if (ret)
		return ret;

	flush_delayed_work(&dev_priv->rps.delayed_resume_work);

	mutex_lock(&dev_priv->rps.hw_lock);

	val = intel_freq_opcode(dev_priv, val);

	if (val < dev_priv->rps.min_freq ||
	    val > dev_priv->rps.max_freq ||
	    val < dev_priv->rps.min_freq_softlimit) {
		mutex_unlock(&dev_priv->rps.hw_lock);
		return -EINVAL;
	}

	if (val > dev_priv->rps.rp0_freq)
		DRM_DEBUG("User requested overclocking to %d\n",
			  intel_gpu_freq(dev_priv, val));

	dev_priv->rps.max_freq_softlimit = val;

	val = clamp_t(int, dev_priv->rps.cur_freq,
		      dev_priv->rps.min_freq_softlimit,
		      dev_priv->rps.max_freq_softlimit);


	intel_set_rps(dev, val);

	mutex_unlock(&dev_priv->rps.hw_lock);

	return count;
}
