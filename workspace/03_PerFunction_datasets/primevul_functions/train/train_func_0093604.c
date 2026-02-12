R_API ut64 r_bin_java_code_attr_calc_size(RBinJavaAttrInfo *attr) {
	RListIter *iter;

	ut64 size = 0;
	if (attr) {

		size += 6;

		size += 2;

		size += 2;

		size += 2;
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
