R_API ut64 r_bin_java_code_attr_calc_size(RBinJavaAttrInfo *attr) {
	RListIter *iter;

	ut64 size = 0;
	bool is_attr_in_old_format = attr->is_attr_in_old_format;
	if (attr) {

		size += is_attr_in_old_format ? 4 : 6;

		size += is_attr_in_old_format ? 1 : 2;

		size += is_attr_in_old_format ? 1 : 2;

		size += is_attr_in_old_format ? 2 : 4;
		if (attr->info.code_attr.code) {
			size += attr->info.code_attr.code_length;
		}

		size += 2;


		r_list_foreach_iter (attr->info.code_attr.exception_table, iter) {

			size += 2;

			size += 2;

			size += 2;

			size += 2;
		}

		size += 2;

		if (attr->info.code_attr.attributes_count > 0) {

			r_list_foreach_iter (attr->info.code_attr.attributes, iter) {
				size += r_bin_java_attr_calc_size (attr);
			}
		}
	}
	return size;
}
