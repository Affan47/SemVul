unlink_mount_tree(struct autofs_point *ap, struct mnt_list *mnts)
{
	struct mnt_list *this;
	int rv, ret;
	pid_t pgrp = getpgrp();
	char spgrp[20];

	sprintf(spgrp, "pgrp=%d", pgrp);

	ret = 1;
	this = mnts;
	while (this) {
		if (strstr(this->opts, spgrp)) {
			this = this->next;
			continue;
		}

		if (strcmp(this->fs_type, "autofs"))
			rv = spawn_umount(ap->logopt, "-l", this->path, NULL);
		else
			rv = umount2(this->path, MNT_DETACH);
		if (rv == -1) {
			debug(ap->logopt,
			      "can't unlink %s from mount tree", this->path);

			switch (errno) {
			case EINVAL:
				warn(ap->logopt,
				      "bad superblock or not mounted");
				break;

			case ENOENT:
			case EFAULT:
				ret = 0;
				warn(ap->logopt, "bad path for mount");
				break;
			}
		}
		this = this->next;
	}
	return ret;
}
