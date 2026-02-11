get_unseen_seq_name(void)
{
	static gchar *seq_name = NULL;
	if (!seq_name) {
		gchar buf[BUFFSIZE];
		gchar *tmp;
		gchar *profile_path = g_strconcat(
			get_home_dir(), G_DIR_SEPARATOR_S,
			".mh_profile", NULL);
		FILE *fp = g_fopen(profile_path, "r");
		if (fp) {
			while (fgets(buf, sizeof(buf), fp) != NULL) {
				if (!strncmp(buf, "Unseen-Sequence:", strlen("Unseen-Sequence:"))) {
					gchar *seq_tmp = buf+strlen("Unseen-Sequence:");
					while (*seq_tmp == ' ')
						seq_tmp++;
					seq_name = g_strdup(seq_tmp);
					seq_name = strretchomp(seq_name);
					break;
				}
			}
			fclose(fp);
		}
		if (!seq_name)
			seq_name = g_strdup("unseen");
		tmp = g_strdup_printf("%s:", seq_name);
		g_free(seq_name);
		seq_name = tmp;
	}
	return seq_name;
}
