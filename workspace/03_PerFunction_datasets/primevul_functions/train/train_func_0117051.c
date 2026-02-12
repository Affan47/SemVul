void nested_vmx_vcpu_setup(void)
{
	if (enable_shadow_vmcs) {


		vmcs_write64(VMREAD_BITMAP, __pa(vmx_vmread_bitmap));
		vmcs_write64(VMWRITE_BITMAP, __pa(vmx_vmread_bitmap));
	}
}
