static void prepare_vmcs02_constant_state(struct vcpu_vmx *vmx)
{


	if (vmx->nested.vmcs02_initialized)
		return;
	vmx->nested.vmcs02_initialized = true;


	if (enable_ept && nested_early_check)
		vmcs_write64(EPT_POINTER, construct_eptp(&vmx->vcpu, 0));


	if (cpu_has_vmx_vmfunc())
		vmcs_write64(VM_FUNCTION_CONTROL, 0);

	if (cpu_has_vmx_posted_intr())
		vmcs_write16(POSTED_INTR_NV, POSTED_INTR_NESTED_VECTOR);

	if (cpu_has_vmx_msr_bitmap())
		vmcs_write64(MSR_BITMAP, __pa(vmx->nested.vmcs02.msr_bitmap));

	if (enable_pml)
		vmcs_write64(PML_ADDRESS, page_to_phys(vmx->pml_pg));


	vmcs_write32(VM_EXIT_MSR_STORE_COUNT, 0);
	vmcs_write64(VM_EXIT_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.host.val));
	vmcs_write64(VM_ENTRY_MSR_LOAD_ADDR, __pa(vmx->msr_autoload.guest.val));

	vmx_set_constant_host_state(vmx);
}
