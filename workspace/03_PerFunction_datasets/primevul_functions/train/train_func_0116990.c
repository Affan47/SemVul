static int nested_vmx_handle_enlightened_vmptrld(struct kvm_vcpu *vcpu,
						 bool from_launch)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct hv_vp_assist_page assist_page;

	if (likely(!vmx->nested.enlightened_vmcs_enabled))
		return 1;

	if (unlikely(!kvm_hv_get_assist_page(vcpu, &assist_page)))
		return 1;

	if (unlikely(!assist_page.enlighten_vmentry))
		return 1;

	if (unlikely(assist_page.current_nested_vmcs !=
		     vmx->nested.hv_evmcs_vmptr)) {

		if (!vmx->nested.hv_evmcs)
			vmx->nested.current_vmptr = -1ull;

		nested_release_evmcs(vcpu);

		vmx->nested.hv_evmcs_page = kvm_vcpu_gpa_to_page(
			vcpu, assist_page.current_nested_vmcs);

		if (unlikely(is_error_page(vmx->nested.hv_evmcs_page)))
			return 0;

		vmx->nested.hv_evmcs = kmap(vmx->nested.hv_evmcs_page);


		if ((vmx->nested.hv_evmcs->revision_id != KVM_EVMCS_VERSION) &&
		    (vmx->nested.hv_evmcs->revision_id != VMCS12_REVISION)) {
			nested_release_evmcs(vcpu);
			return 0;
		}

		vmx->nested.dirty_vmcs12 = true;


		vmx->nested.hv_evmcs->hv_clean_fields &=
			~HV_VMX_ENLIGHTENED_CLEAN_FIELD_ALL;
		vmx->nested.hv_evmcs_vmptr = assist_page.current_nested_vmcs;


		if (from_launch) {
			struct vmcs12 *vmcs12 = get_vmcs12(vcpu);
			memset(vmcs12, 0, sizeof(*vmcs12));
			vmcs12->hdr.revision_id = VMCS12_REVISION;
		}

	}
	return 1;
}
