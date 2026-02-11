i915_gpu_busy(void)
{
	struct drm_i915_private *dev_priv;
	struct intel_engine_cs *ring;
	bool ret = false;
	int i;

	spin_lock_irq(&mchdev_lock);
	if (!i915_mch_dev)
		goto out_unlock;
	dev_priv = i915_mch_dev;

	for_each_ring(ring, dev_priv, i)
		ret |= !list_empty(&ring->request_list);

out_unlock:
	spin_unlock_irq(&mchdev_lock);

	return ret;
}
