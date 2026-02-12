static int __mtab_find_umount_fs(struct libmnt_context *cxt,
			    const char *tgt,
			    struct libmnt_fs **pfs)
{
	int rc;
	struct libmnt_ns *ns_old;
	struct libmnt_table *mtab = NULL;
	struct libmnt_fs *fs;
	char *loopdev = NULL;

	assert(cxt);
	assert(tgt);
	assert(pfs);

	*pfs = NULL;
	DBG(CXT, ul_debugobj(cxt, " search %s in mountinfo", tgt));


	if (mnt_context_is_nocanonicalize(cxt) &&
	    !mnt_context_mtab_writable(cxt) && *tgt == '/')
		rc = mnt_context_get_mtab_for_target(cxt, &mtab, tgt);
	else
		rc = mnt_context_get_mtab(cxt, &mtab);

	if (rc) {
		DBG(CXT, ul_debugobj(cxt, "umount: failed to read mtab"));
		return rc;
	}

	if (mnt_table_get_nents(mtab) == 0) {
		DBG(CXT, ul_debugobj(cxt, "umount: mtab empty"));
		return 1;
	}

	ns_old = mnt_context_switch_target_ns(cxt);
	if (!ns_old)
		return -MNT_ERR_NAMESPACE;

try_loopdev:
	fs = mnt_table_find_target(mtab, tgt, MNT_ITER_BACKWARD);
	if (!fs && mnt_context_is_swapmatch(cxt)) {


		fs = mnt_table_find_source(mtab, tgt, MNT_ITER_BACKWARD);

		if (fs) {
			struct libmnt_fs *fs1 = mnt_table_find_target(mtab,
							mnt_fs_get_target(fs),
							MNT_ITER_BACKWARD);
			if (!fs1) {
				DBG(CXT, ul_debugobj(cxt, "mtab is broken?!?!"));
				rc = -EINVAL;
				goto err;
			}
			if (fs != fs1) {


				DBG(CXT, ul_debugobj(cxt,
						"umount: %s: %s is mounted "
						"over it on the same point",
						tgt, mnt_fs_get_source(fs1)));
				rc = -EINVAL;
				goto err;
			}
		}
	}

	if (!fs && !loopdev && mnt_context_is_swapmatch(cxt)) {


		struct stat st;

		if (mnt_stat_mountpoint(tgt, &st) == 0 && S_ISREG(st.st_mode)) {
			int count;
			struct libmnt_cache *cache = mnt_context_get_cache(cxt);
			const char *bf = cache ? mnt_resolve_path(tgt, cache) : tgt;

			count = loopdev_count_by_backing_file(bf, &loopdev);
			if (count == 1) {
				DBG(CXT, ul_debugobj(cxt,
					"umount: %s --> %s (retry)", tgt, loopdev));
				tgt = loopdev;
				goto try_loopdev;

			} else if (count > 1)
				DBG(CXT, ul_debugobj(cxt,
					"umount: warning: %s is associated "
					"with more than one loopdev", tgt));
		}
	}

	*pfs = fs;
	free(loopdev);
	if (!mnt_context_switch_ns(cxt, ns_old))
		return -MNT_ERR_NAMESPACE;

	DBG(CXT, ul_debugobj(cxt, "umount fs: %s", fs ? mnt_fs_get_target(fs) :
							"<not found>"));
	return fs ? 0 : 1;
err:
	free(loopdev);
	if (!mnt_context_switch_ns(cxt, ns_old))
		return -MNT_ERR_NAMESPACE;
	return rc;
}
