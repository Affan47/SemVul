isc_lib_initmsgcat(void) {
	isc_result_t result;


	result = isc_once_do(&msgcat_once, open_msgcat);
	if (result != ISC_R_SUCCESS) {


		fprintf(stderr, "%s:%d: %s: isc_once_do() %s.\n",
			__FILE__, __LINE__,
			isc_msgcat_get(isc_msgcat, ISC_MSGSET_GENERAL,
				       ISC_MSG_FATALERROR, "fatal error"),
			isc_msgcat_get(isc_msgcat, ISC_MSGSET_GENERAL,
				       ISC_MSG_FAILED, "failed"));
		abort();
	}
}
