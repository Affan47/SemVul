R_API void r_bin_java_verification_info_free(void  *o) {
	RBinJavaVerificationObj *obj = o;

	if (obj) {
		free (obj->name);
		free (obj);
	}
}
