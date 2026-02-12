int mnt_optstr_fix_user(char **optstr)
{
	char *username;
	struct libmnt_optloc ol = MNT_INIT_OPTLOC;
	int rc = 0;

	DBG(CXT, ul_debug("fixing user"));

	rc = mnt_optstr_locate_option(*optstr, "user", &ol);
	if (rc)
		return rc == 1 ? 0 : rc;

	username = mnt_get_username(getuid());
	if (!username)
		return -ENOMEM;

	if (!ol.valsz || (ol.value && strncmp(ol.value, username, ol.valsz) != 0)) {
		if (ol.valsz)

			mnt_optstr_remove_option_at(optstr, ol.value, ol.end);

		rc = insert_value(optstr, ol.value ? ol.value : ol.end,
				  username, NULL);
	}

	free(username);
	return rc;
}
