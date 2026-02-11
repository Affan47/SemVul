visorchipset_ioctl(struct file *file, unsigned int cmd,
			       unsigned long arg)
{
	s64 adjustment;
	s64 vrtc_offset;

	switch (cmd) {
	case VMCALL_QUERY_GUEST_VIRTUAL_TIME_OFFSET:

		vrtc_offset = issue_vmcall_query_guest_virtual_time_offset();
		if (copy_to_user((void __user *)arg, &vrtc_offset,
				 sizeof(vrtc_offset))) {
			return -EFAULT;
		}
		return 0;
	case VMCALL_UPDATE_PHYSICAL_TIME:
		if (copy_from_user(&adjustment, (void __user *)arg,
				   sizeof(adjustment))) {
			return -EFAULT;
		}
		return issue_vmcall_update_physical_time(adjustment);
	default:
		return -EFAULT;
	}
}
