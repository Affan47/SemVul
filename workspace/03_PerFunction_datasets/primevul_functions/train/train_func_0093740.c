R_API char *r_bin_java_get_item_name_from_bin_cp_list(RBinJavaObj *bin, RBinJavaCPTypeObj *obj) {
	char *res = NULL;


	if (bin && obj) {
		res = r_bin_java_get_item_name_from_cp_item_list (
			bin->cp_list, obj, MAX_CPITEMS);
	}
	return res;
}
