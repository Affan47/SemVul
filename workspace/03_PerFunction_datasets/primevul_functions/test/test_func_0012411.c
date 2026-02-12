R_API char *r_bin_java_get_desc_from_cp_item_list(RList *cp_list, ut64 idx) {


	RBinJavaCPTypeObj *obj = r_bin_java_get_item_from_cp_item_list (cp_list, idx);
	if (!cp_list) {
		return NULL;
	}
	return r_bin_java_get_item_desc_from_cp_item_list (cp_list, obj, MAX_CPITEMS);
}
