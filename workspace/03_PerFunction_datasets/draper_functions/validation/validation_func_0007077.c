free_debug_handle (MonoDebugHandle *handle)
{
	if (handle->ppdb)
		mono_ppdb_close (handle);
	if (handle->symfile)
		mono_debug_close_mono_symbol_file (handle->symfile);

	mono_image_close (handle->image);
	g_free (handle);
}
