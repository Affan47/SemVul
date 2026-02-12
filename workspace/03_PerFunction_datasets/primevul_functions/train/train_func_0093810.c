R_API char *r_bin_java_get_desc_from_bin_cp_list(RBinJavaObj *bin, ut64 idx) {


	if (bin == NULL) {
		return NULL;
	}
	return r_bin_java_get_desc_from_cp_item_list (bin->cp_list, idx);
}
