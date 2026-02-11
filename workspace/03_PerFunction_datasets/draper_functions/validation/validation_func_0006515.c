plain_init(char *params, int *timeout)
{
	FILE *fp;
	struct stat st;
	char file1[PATH_MAX], file2[PATH_MAX];
	int i;

	for (i = 0; i < 1 << HASH_ORDER; i++) {
		INIT_LIST_HEAD(&trgt_acct_in[i]);
		INIT_LIST_HEAD(&trgt_acct_out[i]);
	}

	snprintf(file1, sizeof(file1), "%s%s", CONFIG_DIR, INI_DENY_FILE);
	snprintf(file2, sizeof(file2), "/etc/%s", INI_DENY_FILE);

	if (!stat(file1, &st) || !stat(file2, &st))
		log_warning("%s is depreciated and will be obsoleted in the next release, please see README.initiators for more information", INI_DENY_FILE);

	snprintf(file1, sizeof(file1), "%s%s", CONFIG_DIR, CONFIG_FILE);
	snprintf(file2, sizeof(file2), "/etc/%s", CONFIG_FILE);

	if (!(fp = fopen(params ? params : file1, "r"))) {
		if ((fp = fopen(file2, "r")))
			log_warning("%s's location is depreciated and will be moved in the next release to %s", file2, file1);
		else {
			log_warning("%s not found, configure through ietadm", CONFIG_FILE);
			return;
		}
	}

	plain_portal_init(fp, timeout);

	rewind(fp);

	plain_target_init(fp);

	rewind(fp);

	plain_account_init(fp);

	fclose(fp);

	return;
}
