xen_efi_query_capsule_caps(efi_capsule_header_t **capsules,
					       unsigned long count,
					       u64 *max_size,
					       int *reset_type)
{
	struct xen_platform_op op = INIT_EFI_OP(query_capsule_capabilities);

	if (efi.runtime_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		return EFI_UNSUPPORTED;

	set_xen_guest_handle(efi_data(op).u.query_capsule_capabilities.capsule_header_array,
					capsules);
	efi_data(op).u.query_capsule_capabilities.capsule_count = count;

	if (HYPERVISOR_dom0_op(&op) < 0)
		return EFI_UNSUPPORTED;

	*max_size = efi_data(op).u.query_capsule_capabilities.max_capsule_size;
	*reset_type = efi_data(op).u.query_capsule_capabilities.reset_type;

	return efi_data(op).status;
}
