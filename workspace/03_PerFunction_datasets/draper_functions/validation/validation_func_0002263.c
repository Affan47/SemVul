i915_gem_init_userptr(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	mutex_init(&dev_priv->mm_lock);
	hash_init(dev_priv->mm_structs);
	return 0;
}
