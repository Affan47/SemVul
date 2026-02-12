R_API ut64 r_bin_java_element_pair_calc_size(RBinJavaElementValuePair *ev_pair) {
	ut64 sz = 0;
	if (ev_pair == NULL) {
		return sz;
	}

	sz += 2;

	if (ev_pair->value) {
		sz += r_bin_java_element_value_calc_size (ev_pair->value);
	}
	return sz;
}
