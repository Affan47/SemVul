static int inode_doinit_with_dentry(struct inode *inode, struct dentry *opt_dentry)
{
	struct superblock_security_struct *sbsec = NULL;
	struct inode_security_struct *isec = selinux_inode(inode);
	u32 task_sid, sid = 0;
	u16 sclass;
	struct dentry *dentry;
	int rc = 0;

	if (isec->initialized == LABEL_INITIALIZED)
		return 0;

	spin_lock(&isec->lock);
	if (isec->initialized == LABEL_INITIALIZED)
		goto out_unlock;

	if (isec->sclass == SECCLASS_FILE)
		isec->sclass = inode_mode_to_security_class(inode->i_mode);

	sbsec = selinux_superblock(inode->i_sb);
	if (!(sbsec->flags & SE_SBINITIALIZED)) {


		spin_lock(&sbsec->isec_lock);
		if (list_empty(&isec->list))
			list_add(&isec->list, &sbsec->isec_head);
		spin_unlock(&sbsec->isec_lock);
		goto out_unlock;
	}

	sclass = isec->sclass;
	task_sid = isec->task_sid;
	sid = isec->sid;
	isec->initialized = LABEL_PENDING;
	spin_unlock(&isec->lock);

	switch (sbsec->behavior) {
	case SECURITY_FS_USE_NATIVE:
		break;
	case SECURITY_FS_USE_XATTR:
		if (!(inode->i_opflags & IOP_XATTR)) {
			sid = sbsec->def_sid;
			break;
		}


		if (opt_dentry) {

			dentry = dget(opt_dentry);
		} else {


			dentry = d_find_alias(inode);
			if (!dentry)
				dentry = d_find_any_alias(inode);
		}
		if (!dentry) {


			goto out_invalid;
		}

		rc = inode_doinit_use_xattr(inode, dentry, sbsec->def_sid,
					    &sid);
		dput(dentry);
		if (rc)
			goto out;
		break;
	case SECURITY_FS_USE_TASK:
		sid = task_sid;
		break;
	case SECURITY_FS_USE_TRANS:

		sid = sbsec->sid;


		rc = security_transition_sid(&selinux_state, task_sid, sid,
					     sclass, NULL, &sid);
		if (rc)
			goto out;
		break;
	case SECURITY_FS_USE_MNTPOINT:
		sid = sbsec->mntpoint_sid;
		break;
	default:

		sid = sbsec->sid;

		if ((sbsec->flags & SE_SBGENFS) &&
		     (!S_ISLNK(inode->i_mode) ||
		      selinux_policycap_genfs_seclabel_symlinks())) {


			if (opt_dentry) {


				dentry = dget(opt_dentry);
			} else {


				dentry = d_find_alias(inode);
				if (!dentry)
					dentry = d_find_any_alias(inode);
			}


			if (!dentry)
				goto out_invalid;
			rc = selinux_genfs_get_sid(dentry, sclass,
						   sbsec->flags, &sid);
			if (rc) {
				dput(dentry);
				goto out;
			}

			if ((sbsec->flags & SE_SBGENFS_XATTR) &&
			    (inode->i_opflags & IOP_XATTR)) {
				rc = inode_doinit_use_xattr(inode, dentry,
							    sid, &sid);
				if (rc) {
					dput(dentry);
					goto out;
				}
			}
			dput(dentry);
		}
		break;
	}

out:
	spin_lock(&isec->lock);
	if (isec->initialized == LABEL_PENDING) {
		if (rc) {
			isec->initialized = LABEL_INVALID;
			goto out_unlock;
		}
		isec->initialized = LABEL_INITIALIZED;
		isec->sid = sid;
	}

out_unlock:
	spin_unlock(&isec->lock);
	return rc;

out_invalid:
	spin_lock(&isec->lock);
	if (isec->initialized == LABEL_PENDING) {
		isec->initialized = LABEL_INVALID;
		isec->sid = sid;
	}
	spin_unlock(&isec->lock);
	return 0;
}
