R_API ut64 r_bin_java_signature_attr_calc_size(RBinJavaAttrInfo *attr) {
	ut64 size = 0;
	if (attr == NULL) {

		return size;
	}
	size += 6;

	size += 2;

	size += 2;
	return size;
}
