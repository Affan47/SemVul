R_API void r_bin_java_utf8_info_free(void  *o) {
	RBinJavaCPTypeObj *obj = o;
	if (obj) {
		free (obj->name);
		free (obj->metas);
		free (obj->info.cp_utf8.bytes);
		free (obj);
	}
}
