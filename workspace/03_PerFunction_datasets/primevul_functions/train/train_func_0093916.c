R_API ut64 r_bin_java_inner_class_attr_calc_size(RBinJavaClassesAttribute *icattr) {
	ut64 size = 0;
	if (icattr) {

		size += 2;

		size += 2;

		size += 2;

		size += 2;
	}
	return size;
}
