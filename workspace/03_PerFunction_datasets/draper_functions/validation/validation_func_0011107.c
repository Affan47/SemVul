i915_suspend_switcheroo(struct drm_device *dev, pm_message_t state)
{
	int error;

	if (!dev || !dev->dev_private) {
		DRM_ERROR("dev: %p\n", dev);
		DRM_ERROR("DRM not initialized, aborting suspend.\n");
		return -ENODEV;
	}

	if (WARN_ON_ONCE(state.event != PM_EVENT_SUSPEND &&
			 state.event != PM_EVENT_FREEZE))
		return -EINVAL;

	if (dev->switch_power_state == DRM_SWITCH_POWER_OFF)
		return 0;

	error = i915_drm_suspend(dev);
	if (error)
		return error;

	return i915_drm_suspend_late(dev, false);
}
