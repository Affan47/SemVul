procmsg_msginfo_get_full_info(MsgInfo *msginfo)
{
	MsgInfo *full_msginfo;
	gchar *file;

	if (msginfo == NULL) return NULL;

	file = procmsg_get_message_file_path(msginfo);
	if (!file || !is_file_exist(file)) {
		g_free(file);
		file = procmsg_get_message_file(msginfo);
	}
	if (!file || !is_file_exist(file)) {
		g_warning("procmsg_msginfo_get_full_info(): can't get message file.\n");
		return NULL;
	}

	full_msginfo = procmsg_msginfo_get_full_info_from_file(msginfo, file);
	g_free(file);
	return full_msginfo;
}
