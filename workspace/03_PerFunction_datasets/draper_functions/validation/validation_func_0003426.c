i915_gem_set_seqno(struct drm_device *dev, u32 seqno)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	int ret;

	if (seqno == 0)
		return -EINVAL;


	ret = i915_gem_init_seqno(dev, seqno - 1);
	if (ret)
		return ret;


	dev_priv->next_seqno = seqno;
	dev_priv->last_seqno = seqno - 1;
	if (dev_priv->last_seqno == 0)
		dev_priv->last_seqno--;

	return 0;
}
