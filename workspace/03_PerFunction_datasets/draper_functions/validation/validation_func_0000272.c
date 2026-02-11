mp4_report(GF_SceneLoader *load, GF_Err e, char *format, ...)
{
#ifndef GPAC_DISABLE_LOG
	if (gf_log_tool_level_on(GF_LOG_PARSER, e ? GF_LOG_ERROR : GF_LOG_WARNING)) {
		char szMsg[1024];
		va_list args;
		va_start(args, format);
		vsprintf(szMsg, format, args);
		va_end(args);
		GF_LOG((u32) (e ? GF_LOG_ERROR : GF_LOG_WARNING), GF_LOG_PARSER, ("[MP4 Loading] %s\n", szMsg) );
	}
#endif
}
