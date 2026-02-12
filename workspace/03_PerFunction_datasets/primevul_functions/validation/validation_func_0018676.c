static int avic_incomplete_ipi_interception(struct vcpu_svm *svm)
{
	u32 icrh = svm->vmcb->control.exit_info_1 >> 32;
	u32 icrl = svm->vmcb->control.exit_info_1;
	u32 id = svm->vmcb->control.exit_info_2 >> 32;
	u32 index = svm->vmcb->control.exit_info_2 & 0xFF;
	struct kvm_lapic *apic = svm->vcpu.arch.apic;

	trace_kvm_avic_incomplete_ipi(svm->vcpu.vcpu_id, icrh, icrl, id, index);

	switch (id) {
	case AVIC_IPI_FAILURE_INVALID_INT_TYPE:


		kvm_lapic_reg_write(apic, APIC_ICR2, icrh);
		kvm_lapic_reg_write(apic, APIC_ICR, icrl);
		break;
	case AVIC_IPI_FAILURE_TARGET_NOT_RUNNING: {
		int i;
		struct kvm_vcpu *vcpu;
		struct kvm *kvm = svm->vcpu.kvm;
		struct kvm_lapic *apic = svm->vcpu.arch.apic;


		kvm_for_each_vcpu(i, vcpu, kvm) {
			bool m = kvm_apic_match_dest(vcpu, apic,
						     icrl & APIC_SHORT_MASK,
						     GET_APIC_DEST_FIELD(icrh),
						     icrl & APIC_DEST_MASK);

			if (m && !avic_vcpu_is_running(vcpu))
				kvm_vcpu_wake_up(vcpu);
		}
		break;
	}
	case AVIC_IPI_FAILURE_INVALID_TARGET:
		WARN_ONCE(1, "Invalid IPI target: index=%u, vcpu=%d, icr=%#0x:%#0x\n",
			  index, svm->vcpu.vcpu_id, icrh, icrl);
		break;
	case AVIC_IPI_FAILURE_INVALID_BACKING_PAGE:
		WARN_ONCE(1, "Invalid backing page\n");
		break;
	default:
		pr_err("Unknown IPI interception\n");
	}

	return 1;
}
