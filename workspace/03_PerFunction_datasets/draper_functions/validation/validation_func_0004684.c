find_config_file(gchar *filename){
	gchar fullpath[512];
	gboolean ret;

	LOG(LOG_DEBUG, "IN : find_config_file(%s)", filename);

	sprintf(fullpath, "%s%s%s", user_dir, DIR_DELIMITER, filename);

        ret = find_file(fullpath);

	LOG(LOG_DEBUG, "OUT : find_config_file()");
	return(ret);
}
