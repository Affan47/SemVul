hfinfo_bitoffset(const header_field_info *hfinfo)
{
	if (!hfinfo->bitmask) {
		return 0;
	}


	return hfinfo_container_bitwidth(hfinfo) - 1 - ws_ilog2(hfinfo->bitmask);
}
