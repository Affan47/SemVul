amdgpu_cgs_get_pci_resource(void *cgs_device,
				       enum cgs_resource_type resource_type,
				       uint64_t size,
				       uint64_t offset,
				       uint64_t *resource_base)
{
	CGS_FUNC_ADEV;

	if (resource_base == NULL)
		return -EINVAL;

	switch (resource_type) {
	case CGS_RESOURCE_TYPE_MMIO:
		if (adev->rmmio_size == 0)
			return -ENOENT;
		if ((offset + size) > adev->rmmio_size)
			return -EINVAL;
		*resource_base = adev->rmmio_base;
		return 0;
	case CGS_RESOURCE_TYPE_DOORBELL:
		if (adev->doorbell.size == 0)
			return -ENOENT;
		if ((offset + size) > adev->doorbell.size)
			return -EINVAL;
		*resource_base = adev->doorbell.base;
		return 0;
	case CGS_RESOURCE_TYPE_FB:
	case CGS_RESOURCE_TYPE_IO:
	case CGS_RESOURCE_TYPE_ROM:
	default:
		return -EINVAL;
	}
}
