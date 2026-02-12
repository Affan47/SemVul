static RzList  *parse_aranges_raw(const ut8 *obuf, size_t obuf_sz, bool big_endian) {
	rz_return_val_if_fail(obuf, NULL);
	const ut8 *buf = obuf;
	const ut8 *buf_end = buf + obuf_sz;

	RzList *r = rz_list_newf((RzListFree)rz_bin_dwarf_arange_set_free);
	if (!r) {
		return NULL;
	}


	while (buf < buf_end) {
		const ut8 *start = buf;
		bool is_64bit;
		ut64 unit_length = dwarf_read_initial_length(&is_64bit, big_endian, &buf, buf_end);


		size_t header_rest_size = 2 + (is_64bit ? 8 : 4) + 1 + 1;
		if (unit_length < header_rest_size || unit_length > buf_end - buf) {
			break;
		}
		const ut8 *next_set_buf = buf + unit_length;
		RzBinDwarfARangeSet *set = RZ_NEW(RzBinDwarfARangeSet);
		if (!set) {
			break;
		}
		set->unit_length = unit_length;
		set->is_64bit = is_64bit;
		set->version = READ16(buf);
		set->debug_info_offset = dwarf_read_offset(set->is_64bit, big_endian, &buf, buf_end);
		set->address_size = READ8(buf);
		set->segment_size = READ8(buf);
		unit_length -= header_rest_size;
		if (!set->address_size) {
			free(set);
			break;
		}


		size_t off = buf - start;
		size_t pad = rz_num_align_delta(off, 2 * set->address_size);
		if (pad > unit_length || pad > buf_end - buf) {
			free(set);
			break;
		}
		buf += pad;
		unit_length -= pad;

		size_t arange_size = 2 * set->address_size;
		set->aranges_count = unit_length / arange_size;
		if (!set->aranges_count) {
			free(set);
			break;
		}
		set->aranges = RZ_NEWS0(RzBinDwarfARange, set->aranges_count);
		if (!set->aranges) {
			free(set);
			break;
		}
		size_t i;
		for (i = 0; i < set->aranges_count; i++) {
			set->aranges[i].addr = dwarf_read_address(set->address_size, big_endian, &buf, buf_end);
			set->aranges[i].length = dwarf_read_address(set->address_size, big_endian, &buf, buf_end);
			if (!set->aranges[i].addr && !set->aranges[i].length) {

				i++;
				break;
			}
		}
		set->aranges_count = i;
		buf = next_set_buf;
		rz_list_push(r, set);
	}

	return r;
}
