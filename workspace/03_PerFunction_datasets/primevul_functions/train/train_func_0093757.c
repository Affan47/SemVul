R_API RBinJavaAttrInfo *r_bin_java_get_attr_from_field(RBinJavaField *field, R_BIN_JAVA_ATTR_TYPE attr_type, ut32 pos) {


	RBinJavaAttrInfo *attr = NULL, *item;
	RListIter *iter;
	ut32 i = 0;
	if (field) {
		r_list_foreach (field->attributes, iter, item) {

			if ((i++) >= pos) {
				if (item && (item->type == attr_type)) {
					attr = item;
					break;
				}
			}
		}
	}
	return attr;
}
