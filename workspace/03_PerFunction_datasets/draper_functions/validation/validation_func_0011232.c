xen_hvm_need_lapic(void)
{
	if (xen_nopv)
		return false;
	if (xen_pv_domain())
		return false;
	if (!xen_hvm_domain())
		return false;
	if (xen_feature(XENFEAT_hvm_pirqs) && xen_have_vector_callback)
		return false;
	return true;
}
