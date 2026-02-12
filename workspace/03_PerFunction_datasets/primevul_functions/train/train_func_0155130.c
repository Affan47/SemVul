kvm_calc_nested_mmu_role(struct kvm_vcpu *vcpu, struct kvm_mmu_role_regs *regs)
{
	union kvm_mmu_role role;

	role = kvm_calc_shadow_root_page_role_common(vcpu, regs, false);


	role.base.direct = true;
	role.base.level = role_regs_to_root_level(regs);
	return role;
}
