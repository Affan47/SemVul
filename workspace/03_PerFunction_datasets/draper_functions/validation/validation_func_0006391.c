read_conf_file(char *conf_file)
{
	FILE *stream;
	char *path;
	int ret;

	glob_t globbuf;

	globbuf.gl_offs = 0;
	glob(conf_file, 0, NULL, &globbuf);

	int i;
	for(i = 0; i < globbuf.gl_pathc; i++){
		log_message(LOG_INFO, "Opening file '%s'.", globbuf.gl_pathv[i]);
		stream = fopen(globbuf.gl_pathv[i], "r");
		if (!stream) {
			log_message(LOG_INFO, "Configuration file '%s' open problem (%s)..."
				       , globbuf.gl_pathv[i], strerror(errno));
			return;
		}
		current_stream = stream;
		current_conf_file = globbuf.gl_pathv[i];

		char prev_path[MAXBUF];
		path = getcwd(prev_path, MAXBUF);
		if (!path) {
			log_message(LOG_INFO, "getcwd(%s) error (%s)"
					    , prev_path, strerror(errno));
		}

		char *confpath = strdup(globbuf.gl_pathv[i]);
		dirname(confpath);
		ret = chdir(confpath);
		if (ret < 0) {
			log_message(LOG_INFO, "chdir(%s) error (%s)"
					    , confpath, strerror(errno));
		}
		process_stream(current_keywords);
		fclose(stream);

		ret = chdir(prev_path);
		if (ret < 0) {
			log_message(LOG_INFO, "chdir(%s) error (%s)"
					    , prev_path, strerror(errno));
		}
	}

	globfree(&globbuf);
}
