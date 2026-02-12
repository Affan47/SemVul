R_API char *r_bin_java_get_item_desc_from_bin_cp_list(RBinJavaObj *bin, RBinJavaCPTypeObj *obj) {


	return bin? r_bin_java_get_item_desc_from_cp_item_list (bin->cp_list, obj, MAX_CPITEMS): NULL;
}
