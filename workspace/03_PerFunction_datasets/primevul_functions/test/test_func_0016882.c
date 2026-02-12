static const ut8 *info_comp_unit_read_hdr(const ut8 *buf, const ut8 *buf_end, RzBinDwarfCompUnitHdr *hdr, bool big_endian) {


	hdr->length = READ32(buf);
	if (hdr->length == (ut32)DWARF_INIT_LEN_64) {
		hdr->length = READ64(buf);
		hdr->is_64bit = true;
	}
	const ut8 *tmp = buf;
	hdr->version = READ16(buf);
	if (hdr->version == 5) {
		hdr->unit_type = READ8(buf);
		hdr->address_size = READ8(buf);
		hdr->abbrev_offset = dwarf_read_offset(hdr->is_64bit, big_endian, &buf, buf_end);

		if (hdr->unit_type == DW_UT_skeleton || hdr->unit_type == DW_UT_split_compile) {
			hdr->dwo_id = READ8(buf);
		} else if (hdr->unit_type == DW_UT_type || hdr->unit_type == DW_UT_split_type) {
			hdr->type_sig = READ64(buf);
			hdr->type_offset = dwarf_read_offset(hdr->is_64bit, big_endian, &buf, buf_end);
		}
	} else {
		hdr->abbrev_offset = dwarf_read_offset(hdr->is_64bit, big_endian, &buf, buf_end);
		hdr->address_size = READ8(buf);
	}
	hdr->header_size = buf - tmp;
	return buf;
}
