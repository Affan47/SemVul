R_API ut64 rbin_java_verification_info_calc_size(RBinJavaVerificationObj *se) {
	ut64 sz = 1;
	if (!se) {
		return 0;
	}

	switch (se->tag) {
	case R_BIN_JAVA_STACKMAP_OBJECT:

		sz += 2;
		break;
	case R_BIN_JAVA_STACKMAP_UNINIT:

		sz += 2;
		break;
	}
	return sz;
}
