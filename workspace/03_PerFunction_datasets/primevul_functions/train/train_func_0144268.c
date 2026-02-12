PS_GC_FUNC(files)
{
	PS_FILES_DATA;


	if (data->dirdepth == 0) {
		*nrdels = ps_files_cleanup_dir(data->basedir, maxlifetime TSRMLS_CC);
	}

	return SUCCESS;
}
