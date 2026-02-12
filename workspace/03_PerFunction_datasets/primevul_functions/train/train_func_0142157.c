static int kvmgt_inject_msi(unsigned long handle, u32 addr, u16 data)
{
	struct kvmgt_guest_info *info;
	struct intel_vgpu *vgpu;

	if (!handle_valid(handle))
		return -ESRCH;

	info = (struct kvmgt_guest_info *)handle;
	vgpu = info->vgpu;


	if (vgpu->vdev.msi_trigger == NULL)
		return 0;

	if (eventfd_signal(vgpu->vdev.msi_trigger, 1) == 1)
		return 0;

	return -EFAULT;
}
