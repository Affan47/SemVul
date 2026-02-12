R_API RBinJavaAttrInfo *r_bin_java_get_method_code_attribute(const RBinJavaField *method) {


	RBinJavaAttrInfo *res = NULL, *attr = NULL;
	RListIter *iter;
	if (method) {
		r_list_foreach (method->attributes, iter, attr) {
			if (attr && (attr->type == R_BIN_JAVA_ATTR_TYPE_CODE_ATTR)) {
				res = attr;
				break;
			}
		}
	}
	return res;
}
