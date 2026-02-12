bool kvm_is_zone_device_pfn(kvm_pfn_t pfn)
{


	if (!pfn_valid(pfn) || WARN_ON_ONCE(!page_count(pfn_to_page(pfn))))
		return false;

	return is_zone_device_page(pfn_to_page(pfn));
}
