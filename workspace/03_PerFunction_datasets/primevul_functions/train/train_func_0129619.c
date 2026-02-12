static int inode_doinit_with_dentry(struct inode *inode, struct dentry *opt_dentry)
{
	struct superblock_security_struct *sbsec = NULL;
	struct inode_security_struct *isec = inode->i_security;
	u32 sid;
	struct dentry *dentry;
#define INITCONTEXTLEN 255
	char *context = NULL;
	unsigned len = 0;
	int rc = 0;

	if (isec->initialized)
		goto out;

	mutex_lock(&isec->lock);
	if (isec->initialized)
		goto out_unlock;

	sbsec = inode->i_sb->s_security;
	if (!(sbsec->flags & SE_SBINITIALIZED)) {


		spin_lock(&sbsec->isec_lock);
		if (list_empty(&isec->list))
			list_add(&isec->list, &sbsec->isec_head);
		spin_unlock(&sbsec->isec_lock);
		goto out_unlock;
	}

	switch (sbsec->behavior) {
	case SECURITY_FS_USE_NATIVE:
		break;
	case SECURITY_FS_USE_XATTR:
		if (!inode->i_op->getxattr) {
			isec->sid = sbsec->def_sid;
			break;
		}


		if (opt_dentry) {

			dentry = dget(opt_dentry);
		} else {

			dentry = d_find_alias(inode);
		}
		if (!dentry) {


			goto out_unlock;
		}

		len = INITCONTEXTLEN;
		context = kmalloc(len+1, GFP_NOFS);
		if (!context) {
			rc = -ENOMEM;
			dput(dentry);
			goto out_unlock;
		}
		context[len] = '\0';
		rc = inode->i_op->getxattr(dentry, XATTR_NAME_SELINUX,
					   context, len);
		if (rc == -ERANGE) {
			kfree(context);


			rc = inode->i_op->getxattr(dentry, XATTR_NAME_SELINUX,
						   NULL, 0);
			if (rc < 0) {
				dput(dentry);
				goto out_unlock;
			}
			len = rc;
			context = kmalloc(len+1, GFP_NOFS);
			if (!context) {
				rc = -ENOMEM;
				dput(dentry);
				goto out_unlock;
			}
			context[len] = '\0';
			rc = inode->i_op->getxattr(dentry,
						   XATTR_NAME_SELINUX,
						   context, len);
		}
		dput(dentry);
		if (rc < 0) {
			if (rc != -ENODATA) {
				printk(KERN_WARNING "SELinux: %s:  getxattr returned "
				       "%d for dev=%s ino=%ld\n", __func__,
				       -rc, inode->i_sb->s_id, inode->i_ino);
				kfree(context);
				goto out_unlock;
			}

			sid = sbsec->def_sid;
			rc = 0;
		} else {
			rc = security_context_to_sid_default(context, rc, &sid,
							     sbsec->def_sid,
							     GFP_NOFS);
			if (rc) {
				char *dev = inode->i_sb->s_id;
				unsigned long ino = inode->i_ino;

				if (rc == -EINVAL) {
					if (printk_ratelimit())
						printk(KERN_NOTICE "SELinux: inode=%lu on dev=%s was found to have an invalid "
							"context=%s.  This indicates you may need to relabel the inode or the "
							"filesystem in question.\n", ino, dev, context);
				} else {
					printk(KERN_WARNING "SELinux: %s:  context_to_sid(%s) "
					       "returned %d for dev=%s ino=%ld\n",
					       __func__, context, -rc, dev, ino);
				}
				kfree(context);

				rc = 0;
				break;
			}
		}
		kfree(context);
		isec->sid = sid;
		break;
	case SECURITY_FS_USE_TASK:
		isec->sid = isec->task_sid;
		break;
	case SECURITY_FS_USE_TRANS:

		isec->sid = sbsec->sid;


		isec->sclass = inode_mode_to_security_class(inode->i_mode);
		rc = security_transition_sid(isec->task_sid, sbsec->sid,
					     isec->sclass, NULL, &sid);
		if (rc)
			goto out_unlock;
		isec->sid = sid;
		break;
	case SECURITY_FS_USE_MNTPOINT:
		isec->sid = sbsec->mntpoint_sid;
		break;
	default:

		isec->sid = sbsec->sid;

		if ((sbsec->flags & SE_SBPROC) && !S_ISLNK(inode->i_mode)) {


			if (opt_dentry)


				dentry = dget(opt_dentry);
			else


				dentry = d_find_alias(inode);


			if (!dentry)
				goto out_unlock;
			isec->sclass = inode_mode_to_security_class(inode->i_mode);
			rc = selinux_proc_get_sid(dentry, isec->sclass, &sid);
			dput(dentry);
			if (rc)
				goto out_unlock;
			isec->sid = sid;
		}
		break;
	}

	isec->initialized = 1;

out_unlock:
	mutex_unlock(&isec->lock);
out:
	if (isec->sclass == SECCLASS_FILE)
		isec->sclass = inode_mode_to_security_class(inode->i_mode);
	return rc;
}
