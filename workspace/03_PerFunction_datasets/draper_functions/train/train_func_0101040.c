init ( void )
{


	uint16_t select_type_param = slurm_get_select_type_param();
	if (select_type_param & CR_OTHER_CONS_RES)
		plugin_id = 108;
	debug_flags = slurm_get_debug_flags();
	verbose("%s loaded", plugin_name);
	return SLURM_SUCCESS;
}
