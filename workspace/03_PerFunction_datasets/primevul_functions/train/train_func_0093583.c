R_API RBinJavaCPTypeObj *r_bin_java_get_item_from_bin_cp_list(RBinJavaObj *bin, ut64 idx) {


	if (bin == NULL) {
		return NULL;
	}
	if (idx > bin->cp_count || idx == 0) {
		return r_bin_java_get_java_null_cp ();
	}
	return r_bin_java_get_item_from_cp_item_list (bin->cp_list, idx);
}
