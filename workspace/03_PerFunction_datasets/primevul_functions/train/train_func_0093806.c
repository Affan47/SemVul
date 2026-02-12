R_API ut64 r_bin_java_name_and_type_cp_calc_size(RBinJavaCPTypeObj *obj) {
	ut64 size = 0;
	if (obj) {
		size += 1;

		size += 2;

		size += 2;
	}
	return size;
}
