R_API void r_bin_java_code_attr_free(void  *a) {
	RBinJavaAttrInfo *attr = a;
	if (attr) {


		r_bin_java_stack_frame_free (attr->info.code_attr.implicit_frame);
		r_list_free (attr->info.code_attr.attributes);
		free (attr->info.code_attr.code);
		r_list_free (attr->info.code_attr.exception_table);
		free (attr->name);
		free (attr->metas);
		free (attr);
	}
}
