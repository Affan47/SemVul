cherryview_irq_uninstall(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;

	if (!dev_priv)
		return;

	I915_WRITE(GEN8_MASTER_IRQ, 0);
	POSTING_READ(GEN8_MASTER_IRQ);

	gen8_gt_irq_reset(dev_priv);

	GEN5_IRQ_RESET(GEN8_PCU_);

	spin_lock_irq(&dev_priv->irq_lock);
	if (dev_priv->display_irqs_enabled)
		vlv_display_irq_reset(dev_priv);
	spin_unlock_irq(&dev_priv->irq_lock);
}
