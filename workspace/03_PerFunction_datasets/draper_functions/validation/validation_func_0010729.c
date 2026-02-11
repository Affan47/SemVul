match_sms_folder_str(const char *str)
{
	int i;
	char path[128];

	sprintf(path, "C:\\predefmessages\\%s\\", str);
	for (i = 0; (s40_30_mt_mappings[i].path != NULL) && strcmp(path, s40_30_mt_mappings[i].path); i++) {
#if 0
		dprintf("comparing %s and %s\n", path, s40_30_mt_mappings[i].path);
#endif
	}
	if (s40_30_mt_mappings[i].path == NULL)
		return -1;
	else
		return i;
}
