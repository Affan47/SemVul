RZ_API HtUP  *rz_bin_dwarf_parse_loc(RzBinFile *binfile, int addr_size) {
	rz_return_val_if_fail(binfile, NULL);

	size_t len = 0;
	ut8 *buf = get_section_bytes(binfile, "debug_loc", &len);
	if (!buf) {
		return NULL;
	}
	HtUP  *loc_table = ht_up_new0();
	if (!loc_table) {
		free(buf);
		return NULL;
	}
	loc_table = parse_loc_raw(loc_table, buf, len, addr_size, binfile->o && binfile->o->info && binfile->o->info->big_endian);
	free(buf);
	return loc_table;
}
