sg_comp_get_tls(unsigned id) {
#ifdef ENABLE_THREADS
	char *glob_buf;
# if defined(HAVE_PTHREAD)
	glob_buf = pthread_getspecific(glob_key);
# elif defined(WIN32)
	glob_buf = TlsGetValue(glob_tls_idx);
	if((NULL == glob_buf) && (ERROR_SUCCESS != GetLastError())){
		RETURN_WITH_SET_ERROR("globals", SG_ERROR_MEMSTATUS, NULL);
	}
# endif
#endif

	if( NULL == glob_buf )
		glob_buf = sg_alloc_globals();

	if(  NULL == glob_buf )
		return NULL;

	id -= GLOB_MASK;
	if( id >= lengthof(comp_info) ) {
		SET_ERROR("globals", SG_ERROR_INVALID_ARGUMENT, "sg_comp_get_tls: invalid id (%u)", id);
		return NULL;
	}

	TRACE_LOG_FMT("globals", "get_global_static(%u): %p", id, glob_buf + comp_info[id].glob_ofs);
	return glob_buf + comp_info[id].glob_ofs;
}
