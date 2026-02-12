R_API ut64 r_bin_java_local_variable_table_attr_calc_size(RBinJavaAttrInfo *attr) {
	ut64 size = 0;

	RListIter *iter;

	if (!attr) {
		return 0LL;
	}
	size += 6;

	size += 2;

	r_list_foreach_iter (attr->info.local_variable_table_attr.local_variable_table, iter) {

		size += 2;

		size += 2;

		size += 2;

		size += 2;

		size += 2;
	}
	return size;
}
