R_API void r_bin_java_source_code_file_attr_free(void  *a) {
	RBinJavaAttrInfo *attr = a;
	if (attr) {
		free (attr->name);
		free (attr->metas);
		free (attr);
	}
}
