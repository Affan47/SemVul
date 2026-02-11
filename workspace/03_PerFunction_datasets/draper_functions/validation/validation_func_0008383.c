g_slurm_jobcomp_init( char *jobcomp_loc )
{
	int retval = SLURM_SUCCESS;
	char *plugin_type = "jobcomp";
	char *type;

	if (init_run && g_context)
		return retval;

	slurm_mutex_lock( &context_lock );

	if (g_context)
		plugin_context_destroy(g_context);

	type = slurm_get_jobcomp_type();
	g_context = plugin_context_create(
		plugin_type, type, (void **)&ops, syms, sizeof(syms));

	if (!g_context) {
		error("cannot create %s context for %s", plugin_type, type);
		retval = SLURM_ERROR;
		goto done;
	}
	init_run = true;

done:
	xfree(type);
	if (g_context)
		retval = (*(ops.set_loc))(jobcomp_loc);
	slurm_mutex_unlock( &context_lock );
	return retval;
}
