R_API ut64 r_bin_java_line_number_table_attr_calc_size(RBinJavaAttrInfo *attr) {
	ut64 size = 6;

	RListIter *iter;

	if (!attr) {
		return 0LL;
	}

	r_list_foreach_iter (attr->info.line_number_table_attr.line_number_table, iter) {

		size += 2;

		size += 2;
	}
	return size;
}
