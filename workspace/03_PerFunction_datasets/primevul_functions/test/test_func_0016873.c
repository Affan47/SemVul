RZ_API char *rz_bin_dwarf_line_header_get_full_file_path(RZ_NULLABLE const RzBinDwarfDebugInfo *info, const RzBinDwarfLineHeader *header, ut64 file_index) {
	rz_return_val_if_fail(header, NULL);
	if (file_index >= header->file_names_count) {
		return NULL;
	}
	RzBinDwarfLineFileEntry *file = &header->file_names[file_index];
	if (!file->name) {
		return NULL;
	}


	const char *comp_dir = info ? ht_up_find(info->line_info_offset_comp_dir, header->offset, NULL) : NULL;
	const char *include_dir = NULL;
	char *own_str = NULL;
	if (file->id_idx > 0 && file->id_idx - 1 < header->include_dirs_count) {
		include_dir = header->include_dirs[file->id_idx - 1];
		if (include_dir && include_dir[0] != '/' && comp_dir) {
			include_dir = own_str = rz_str_newf("%s/%s/", comp_dir, include_dir);
		}
	} else {
		include_dir = comp_dir;
	}
	if (!include_dir) {
		include_dir = "./";
	}
	char *r = rz_str_newf("%s/%s", include_dir, file->name);
	free(own_str);
	return r;
}
