void kvm_mmu_after_set_cpuid(struct kvm_vcpu *vcpu)
{


	vcpu->arch.root_mmu.mmu_role.ext.valid = 0;
	vcpu->arch.guest_mmu.mmu_role.ext.valid = 0;
	vcpu->arch.nested_mmu.mmu_role.ext.valid = 0;
	kvm_mmu_reset_context(vcpu);


	KVM_BUG_ON(vcpu->arch.last_vmentry_cpu != -1, vcpu->kvm);
}
