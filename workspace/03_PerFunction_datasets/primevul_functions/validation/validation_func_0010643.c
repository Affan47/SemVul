static u16 kvm_hvcall_signal_event(struct kvm_vcpu *vcpu, bool fast, u64 param)
{
	struct kvm_hv *hv = to_kvm_hv(vcpu->kvm);
	struct eventfd_ctx *eventfd;

	if (unlikely(!fast)) {
		int ret;
		gpa_t gpa = param;

		if ((gpa & (__alignof__(param) - 1)) ||
		    offset_in_page(gpa) + sizeof(param) > PAGE_SIZE)
			return HV_STATUS_INVALID_ALIGNMENT;

		ret = kvm_vcpu_read_guest(vcpu, gpa, &param, sizeof(param));
		if (ret < 0)
			return HV_STATUS_INVALID_ALIGNMENT;
	}


	if (param & 0xffff00000000ULL)
		return HV_STATUS_INVALID_PORT_ID;

	if (param & ~KVM_HYPERV_CONN_ID_MASK)
		return HV_STATUS_INVALID_HYPERCALL_INPUT;


	rcu_read_lock();
	eventfd = idr_find(&hv->conn_to_evt, param);
	rcu_read_unlock();
	if (!eventfd)
		return HV_STATUS_INVALID_PORT_ID;

	eventfd_signal(eventfd, 1);
	return HV_STATUS_SUCCESS;
}
