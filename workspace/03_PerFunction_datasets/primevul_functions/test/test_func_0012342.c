R_API void *r_bin_java_free(RBinJavaObj *bin) {
	char *bin_obj_key = NULL;
	if (!bin) {
		return NULL;
	}

	bin_obj_key = r_bin_java_build_obj_key (bin);


	free (bin_obj_key);
	r_list_free (bin->imports_list);


	r_list_free (bin->cp_list);

	r_list_free (bin->fields_list);

	r_list_free (bin->methods_list);

	r_list_free (bin->interfaces_list);
	r_list_free (bin->attrs_list);


	free (bin->cf2.flags_str);
	free (bin->cf2.this_class_name);
	if (bin == R_BIN_JAVA_GLOBAL_BIN) {
		R_BIN_JAVA_GLOBAL_BIN = NULL;
	}
	free (bin->file);
	r_str_constpool_fini (&bin->constpool);
	free (bin);
	return NULL;
}
