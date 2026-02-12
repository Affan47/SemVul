static int selinux_is_sblabel_mnt(struct super_block *sb)
{
	struct superblock_security_struct *sbsec = sb->s_security;

	if (sbsec->behavior == SECURITY_FS_USE_XATTR ||
	    sbsec->behavior == SECURITY_FS_USE_TRANS ||
	    sbsec->behavior == SECURITY_FS_USE_TASK)
		return 1;


	if (strncmp(sb->s_type->name, "sysfs", sizeof("sysfs")) == 0)
		return 1;


	if (strncmp(sb->s_type->name, "rootfs", sizeof("rootfs")) == 0)
		return 1;

	return 0;
}
