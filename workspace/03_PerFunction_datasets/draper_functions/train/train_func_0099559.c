ay_add_auto_conversation(eb_local_account *ela,
			      const char *name, int public)
{
	FILE *fp;
	char buff[4096];
	snprintf(buff, 4095, "%schatroom_autoconnect", config_dir);

	if (!ela || !name)
		return;

	eb_debug(DBG_CORE, "buff %s\n", buff);

	if ((fp = fopen(buff, "r"))) {
		while (fgets(buff, sizeof(buff), fp)) {
			char **tokens = ay_strsplit(buff, "\t", -1);
			if (!strcmp(tokens[0],
				    get_service_name(ela->service_id))
			    && !strcmp(tokens[1], ela->handle)
			    && !strcmp(tokens[2], name)
			    && atoi(tokens[3]) == public) {
				fclose(fp);
				ay_strfreev(tokens);
				return;
			}
			ay_strfreev(tokens);
		}
		fclose(fp);
	}

	snprintf(buff, 4095, "%schatroom_autoconnect", config_dir);
	fp = fopen(buff, "a");
	if (!fp)
		return;
	fprintf(fp, "%s\t%s\t%s\t%d\t--\n", get_service_name(ela->service_id),
		ela->handle, name, public);
	fclose(fp);
}
