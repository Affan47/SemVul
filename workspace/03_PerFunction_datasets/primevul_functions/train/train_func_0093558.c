R_API ut64 r_bin_java_stack_map_table_attr_calc_size(RBinJavaAttrInfo *attr) {
	ut64 size = 0;
	RListIter *iter, *iter_tmp;
	RBinJavaStackMapFrame *sf;
	if (attr) {

		size += 6;


		size += 2;
		r_list_foreach_safe (attr->info.stack_map_table_attr.stack_map_frame_entries, iter, iter_tmp, sf) {
			size += r_bin_java_stack_map_frame_calc_size (sf);
		}
	}
	return size;
}
