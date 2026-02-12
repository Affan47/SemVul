static void smack_d_instantiate(struct dentry *opt_dentry, struct inode *inode)
{
	struct super_block *sbp;
	struct superblock_smack *sbsp;
	struct inode_smack *isp;
	struct smack_known *skp;
	struct smack_known *ckp = smk_of_current();
	struct smack_known *final;
	char trattr[TRANS_TRUE_SIZE];
	int transflag = 0;
	int rc;
	struct dentry *dp;

	if (inode == NULL)
		return;

	isp = smack_inode(inode);


	if (isp->smk_flags & SMK_INODE_INSTANT)
		return;

	sbp = inode->i_sb;
	sbsp = smack_superblock(sbp);


	final = sbsp->smk_default;


	if (opt_dentry->d_parent == opt_dentry) {
		switch (sbp->s_magic) {
		case CGROUP_SUPER_MAGIC:
		case CGROUP2_SUPER_MAGIC:


			sbsp->smk_root = &smack_known_star;
			sbsp->smk_default = &smack_known_star;
			isp->smk_inode = sbsp->smk_root;
			break;
		case TMPFS_MAGIC:


			isp->smk_inode = smk_of_current();
			break;
		case PIPEFS_MAGIC:
			isp->smk_inode = smk_of_current();
			break;
		case SOCKFS_MAGIC:


			isp->smk_inode = &smack_known_star;
			break;
		default:
			isp->smk_inode = sbsp->smk_root;
			break;
		}
		isp->smk_flags |= SMK_INODE_INSTANT;
		return;
	}


	switch (sbp->s_magic) {
	case SMACK_MAGIC:
	case CGROUP_SUPER_MAGIC:
	case CGROUP2_SUPER_MAGIC:


		final = &smack_known_star;
		break;
	case DEVPTS_SUPER_MAGIC:


		final = ckp;
		break;
	case PROC_SUPER_MAGIC:


		break;
	case TMPFS_MAGIC:


		final = &smack_known_star;


		fallthrough;
	default:


		if (S_ISSOCK(inode->i_mode)) {
			final = &smack_known_star;
			break;
		}


		if (!(inode->i_opflags & IOP_XATTR))
		        break;


		dp = dget(opt_dentry);
		skp = smk_fetch(XATTR_NAME_SMACK, inode, dp);
		if (!IS_ERR_OR_NULL(skp))
			final = skp;


		if (S_ISDIR(inode->i_mode)) {


			if (isp->smk_flags & SMK_INODE_CHANGED) {
				isp->smk_flags &= ~SMK_INODE_CHANGED;
				rc = __vfs_setxattr(&init_user_ns, dp, inode,
					XATTR_NAME_SMACKTRANSMUTE,
					TRANS_TRUE, TRANS_TRUE_SIZE,
					0);
			} else {
				rc = __vfs_getxattr(dp, inode,
					XATTR_NAME_SMACKTRANSMUTE, trattr,
					TRANS_TRUE_SIZE);
				if (rc >= 0 && strncmp(trattr, TRANS_TRUE,
						       TRANS_TRUE_SIZE) != 0)
					rc = -EINVAL;
			}
			if (rc >= 0)
				transflag = SMK_INODE_TRANSMUTE;
		}


		skp = smk_fetch(XATTR_NAME_SMACKEXEC, inode, dp);
		if (IS_ERR(skp) || skp == &smack_known_star ||
		    skp == &smack_known_web)
			skp = NULL;
		isp->smk_task = skp;

		skp = smk_fetch(XATTR_NAME_SMACKMMAP, inode, dp);
		if (IS_ERR(skp) || skp == &smack_known_star ||
		    skp == &smack_known_web)
			skp = NULL;
		isp->smk_mmap = skp;

		dput(dp);
		break;
	}

	if (final == NULL)
		isp->smk_inode = ckp;
	else
		isp->smk_inode = final;

	isp->smk_flags |= (SMK_INODE_INSTANT | transflag);

	return;
}
