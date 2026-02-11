log_debug_toggle(void)
{
	static int	log_level_copy[LOG_ENDCLASS], toggle = 0;

	if (!toggle) {
		LOG_DBG((LOG_MISC, 50, "log_debug_toggle: "
		    "debug levels cleared"));
		memcpy(&log_level_copy, &log_level, sizeof log_level);
		memset(&log_level, 0, sizeof log_level);
	} else {
		memcpy(&log_level, &log_level_copy, sizeof log_level);
		LOG_DBG((LOG_MISC, 50, "log_debug_toggle: "
		    "debug levels restored"));
	}
	toggle = !toggle;
}
