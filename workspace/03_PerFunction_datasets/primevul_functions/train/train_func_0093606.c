R_API char *r_bin_java_get_item_name_from_cp_item_list(RList *cp_list, RBinJavaCPTypeObj *obj, int depth) {


	if (obj == NULL || cp_list == NULL || depth < 0) {
		return NULL;
	}
	switch (obj->tag) {
	case R_BIN_JAVA_CP_NAMEANDTYPE:
		return r_bin_java_get_utf8_from_cp_item_list (
			cp_list, obj->info.cp_name_and_type.name_idx);
	case R_BIN_JAVA_CP_CLASS:
		return r_bin_java_get_utf8_from_cp_item_list (
			cp_list, obj->info.cp_class.name_idx);

	case R_BIN_JAVA_CP_FIELDREF:
	case R_BIN_JAVA_CP_INTERFACEMETHOD_REF:
	case R_BIN_JAVA_CP_METHODREF:
		obj = r_bin_java_get_item_from_cp_item_list (
			cp_list, obj->info.cp_method.name_and_type_idx);
		return r_bin_java_get_item_name_from_cp_item_list (
			cp_list, obj, depth - 1);
	default:
		return NULL;
	case 0:
		IFDBG eprintf("Invalid 0 tag in the constant pool\n");
		return NULL;
	}
	return NULL;
}
