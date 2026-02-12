R_API ut32 r_bin_java_get_utf8_len_from_bin_cp_list(RBinJavaObj *bin, ut64 idx) {


	if (bin == NULL) {
		return 0;
	}
	return r_bin_java_get_utf8_len_from_cp_item_list (bin->cp_list, idx);
}
