analysis_tool_anova_two_factor_engine (G_GNUC_UNUSED GOCmdContext *gcc, data_analysis_output_t *dao, gpointer specs,
				   analysis_tool_engine_t selector, gpointer result)
{
	analysis_tools_data_anova_two_factor_t *info = specs;

	switch (selector) {
	case TOOL_ENGINE_UPDATE_DESCRIPTOR:
		return (dao_command_descriptor (
				dao, (info->replication == 1) ?
				_("Two Factor ANOVA (%s), no replication") :
				_("Two Factor ANOVA (%s),  with replication") , result)
			== NULL);
	case TOOL_ENGINE_UPDATE_DAO:
		if (analysis_tool_anova_two_factor_prepare_input_range (info))
			return TRUE;
		if (info->replication == 1)
			dao_adjust (dao, 7, info->n_c + info->n_r + 12);
		else
			dao_adjust (dao, MAX (2 + info->n_c, 7), info->n_r * 6 + 18);
		return FALSE;
	case TOOL_ENGINE_CLEAN_UP:
		return analysis_tool_anova_two_factor_engine_clean (dao, specs);
	case TOOL_ENGINE_LAST_VALIDITY_CHECK:
		return FALSE;
	case TOOL_ENGINE_PREPARE_OUTPUT_RANGE:
		dao_prepare_output (NULL, dao, _("ANOVA"));
		return FALSE;
	case TOOL_ENGINE_FORMAT_OUTPUT_RANGE:
		return dao_format_output (dao, _("Two Factor ANOVA"));
	case TOOL_ENGINE_PERFORM_CALC:
	default:
		if (info->replication == 1)
			return analysis_tool_anova_two_factor_no_rep_engine_run (dao, info);
		else
			return analysis_tool_anova_two_factor_engine_run (dao, info);
	}
	return TRUE;
}
