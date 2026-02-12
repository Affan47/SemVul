archive_write_disk_set_acls(struct archive *a, int fd, const char *name,
    struct archive_acl *abstract_acl, __LA_MODE_T mode)
{
	(void)a;
	(void)fd;
	(void)name;
	(void)abstract_acl;
	(void)mode;
	return (ARCHIVE_OK);
}
