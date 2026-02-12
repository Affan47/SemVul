R_API ut64 r_bin_java_float_cp_calc_size(RBinJavaCPTypeObj *obj) {
	ut64 size = 0;

	size += 1;

	size += 4;
	return size;
}
