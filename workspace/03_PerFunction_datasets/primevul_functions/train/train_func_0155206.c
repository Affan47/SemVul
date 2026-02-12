static bool page_fault_can_be_fast(struct kvm_page_fault *fault)
{


	if (fault->rsvd)
		return false;


	if (unlikely(fault->exec && fault->present))
		return false;


	return shadow_acc_track_mask != 0 || (fault->write && fault->present);
}
