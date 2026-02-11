copy_drv(struct device_drv *drv)
{
	struct device_drv *copy;

	if (unlikely(!(copy = malloc(sizeof(*copy))))) {
		quit(1, "Failed to allocate device_drv copy of %s (%s)",
				drv->name, drv->copy ? "copy" : "original");
	}
	memcpy(copy, drv, sizeof(*copy));
	copy->copy = true;
	return copy;
}
