static void mlsd_printf(ctrl_t *ctrl, char *buf, size_t len, char *path, char *name, struct stat *st)
{
	char perms[10] = "";
	int ro = !access(path, R_OK);
	int rw = !access(path, W_OK);

	if (S_ISDIR(st->st_mode)) {

		if (ro)
			strlcat(perms, "le", sizeof(perms));
		if (rw)
			strlcat(perms, "pc", sizeof(perms));
	} else {
		if (ro)
			strlcat(perms, "r", sizeof(perms));
		if (rw)
			strlcat(perms, "w", sizeof(perms));
	}

	memset(buf, 0, len);
	if (ctrl->d_num == -1 && (ctrl->list_mode & 0x0F) == 2)
		strlcat(buf, " ", len);

	for (int i = 0; ctrl->facts[i]; i++)
		mlsd_fact(ctrl->facts[i], buf, len, name, perms, st);

	strlcat(buf, " ", len);
	strlcat(buf, name, len);
	strlcat(buf, "\r\n", len);
}
