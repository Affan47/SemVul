unlink(const char *pathname) {
	int result;
	instw_t instw;

	REFCOUNT;

	if (!libc_handle)
		initialize();

#if DEBUG
	debug(2,"unlink(%s)\n",pathname);
#endif


	if( !(__instw.gstatus & INSTW_INITIALIZED) ||
	    !(__instw.gstatus & INSTW_OKWRAP) ) {
		result=true_unlink(pathname);
		return result;
	}

	instw_new(&instw);
	instw_setpath(&instw,pathname);

#if DEBUG
	instw_print(&instw);
#endif

	backup(instw.truepath);
	instw_apply(&instw);

	result=true_unlink(instw.translpath);
	logg("%d\tunlink\t%s\t#%s\n",result,instw.reslvpath,error(result));

	instw_delete(&instw);

	return result;
}
