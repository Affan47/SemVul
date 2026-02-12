int kvm_s390_vcpu_start(struct kvm_vcpu *vcpu)
{
	int i, online_vcpus, r = 0, started_vcpus = 0;

	if (!is_vcpu_stopped(vcpu))
		return 0;

	trace_kvm_s390_vcpu_start_stop(vcpu->vcpu_id, 1);

	spin_lock(&vcpu->kvm->arch.start_stop_lock);
	online_vcpus = atomic_read(&vcpu->kvm->online_vcpus);


	if (kvm_s390_pv_cpu_is_protected(vcpu)) {
		r = kvm_s390_pv_set_cpu_state(vcpu, PV_CPU_STATE_OPR);
		if (r) {
			spin_unlock(&vcpu->kvm->arch.start_stop_lock);
			return r;
		}
	}

	for (i = 0; i < online_vcpus; i++) {
		if (!is_vcpu_stopped(vcpu->kvm->vcpus[i]))
			started_vcpus++;
	}

	if (started_vcpus == 0) {

		__enable_ibs_on_vcpu(vcpu);
	} else if (started_vcpus == 1) {


		__disable_ibs_on_all_vcpus(vcpu->kvm);
	}

	kvm_s390_clear_cpuflags(vcpu, CPUSTAT_STOPPED);


	if (kvm_s390_pv_cpu_is_protected(vcpu))
		vcpu->arch.sie_block->gpsw.mask &= ~PSW_INT_MASK;


	kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
	spin_unlock(&vcpu->kvm->arch.start_stop_lock);
	return 0;
}
