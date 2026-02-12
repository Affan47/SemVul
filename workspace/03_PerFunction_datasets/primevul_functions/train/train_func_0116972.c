static int handle_vmwrite(struct kvm_vcpu *vcpu)
{
	unsigned long field;
	gva_t gva;
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned long exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
	u32 vmx_instruction_info = vmcs_read32(VMX_INSTRUCTION_INFO);


	u64 field_value = 0;
	struct x86_exception e;
	struct vmcs12 *vmcs12;

	if (!nested_vmx_check_permission(vcpu))
		return 1;

	if (vmx->nested.current_vmptr == -1ull)
		return nested_vmx_failInvalid(vcpu);

	if (vmx_instruction_info & (1u << 10))
		field_value = kvm_register_readl(vcpu,
			(((vmx_instruction_info) >> 3) & 0xf));
	else {
		if (get_vmx_mem_address(vcpu, exit_qualification,
				vmx_instruction_info, false, &gva))
			return 1;
		if (kvm_read_guest_virt(vcpu, gva, &field_value,
					(is_64_bit_mode(vcpu) ? 8 : 4), &e)) {
			kvm_inject_page_fault(vcpu, &e);
			return 1;
		}
	}


	field = kvm_register_readl(vcpu, (((vmx_instruction_info) >> 28) & 0xf));


	if (vmcs_field_readonly(field) &&
	    !nested_cpu_has_vmwrite_any_field(vcpu))
		return nested_vmx_failValid(vcpu,
			VMXERR_VMWRITE_READ_ONLY_VMCS_COMPONENT);

	if (!is_guest_mode(vcpu))
		vmcs12 = get_vmcs12(vcpu);
	else {


		if (get_vmcs12(vcpu)->vmcs_link_pointer == -1ull)
			return nested_vmx_failInvalid(vcpu);
		vmcs12 = get_shadow_vmcs12(vcpu);
	}

	if (vmcs12_write_any(vmcs12, field, field_value) < 0)
		return nested_vmx_failValid(vcpu,
			VMXERR_UNSUPPORTED_VMCS_COMPONENT);


	if (!is_guest_mode(vcpu)) {
		switch (field) {
#define SHADOW_FIELD_RW(x) case x:
#include "vmcs_shadow_fields.h"


			break;
		default:
			vmx->nested.dirty_vmcs12 = true;
			break;
		}
	}

	return nested_vmx_succeed(vcpu);
}
