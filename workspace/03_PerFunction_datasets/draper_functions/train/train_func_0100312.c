_e2pcr_read_file (VPATH *localpath, gpointer *filebuffer,
	 gulong filebuffersize)
{
	if (filebuffersize > 0)
	{
		E2_ERR_DECLARE
		 gulong nread;
		if (!e2_fs_get_file_contents (localpath, filebuffer, &nread,
			FALSE E2_ERR_PTR()) || nread < filebuffersize)
		{
			printd (DEBUG, "cannot read whole file");

#ifdef E2_VFS
			e2_fs_set_error_from_errno (&E2_ERR_NAME);
#endif
			e2_fs_error_local (_("Error reading file %s"), localpath E2_ERR_MSGL());
			E2_ERR_CLEAR
			return FALSE;
		}
	}
	return TRUE;
}
