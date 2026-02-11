mono_trace_set_level_string (const char *value)
{
	int i = 0;
	const char *valid_vals[] = {"error", "critical", "warning", "message", "info", "debug", NULL};
	const GLogLevelFlags valid_ids[] = {G_LOG_LEVEL_ERROR, G_LOG_LEVEL_CRITICAL, G_LOG_LEVEL_WARNING,
										G_LOG_LEVEL_MESSAGE, G_LOG_LEVEL_INFO, G_LOG_LEVEL_DEBUG };

	if(!value)
		return;

	while(valid_vals[i]) {
		if(!strcmp(valid_vals[i], value)){
			mono_trace_set_level(valid_ids[i]);
			return;
		}
		i++;
	}

	if(*value)
		g_print("Unknown trace loglevel: %s\n", value);
}
