dir_t_reset(dir_t *ps_dir)
{
	if (ps_dir->entry) free(ps_dir->entry);

	ps_dir->amount 			= 0;
	ps_dir->entry_allocated = 0;

	if(ps_dir->filter) dfilter_free(ps_dir->filter);
	return(0);
}
