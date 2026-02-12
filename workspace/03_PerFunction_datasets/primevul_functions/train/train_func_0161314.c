xfs_fs_remount(
	struct super_block	*sb,
	int			*flags,
	char			*options)
{
	struct xfs_mount	*mp = XFS_M(sb);
	xfs_sb_t		*sbp = &mp->m_sb;
	substring_t		args[MAX_OPT_ARGS];
	char			*p;
	int			error;


	error = xfs_test_remount_options(sb, options);
	if (error)
		return error;

	sync_filesystem(sb);
	while ((p = strsep(&options, ",")) != NULL) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, args);
		switch (token) {
		case Opt_barrier:
			xfs_warn(mp, "%s option is deprecated, ignoring.", p);
			mp->m_flags |= XFS_MOUNT_BARRIER;
			break;
		case Opt_nobarrier:
			xfs_warn(mp, "%s option is deprecated, ignoring.", p);
			mp->m_flags &= ~XFS_MOUNT_BARRIER;
			break;
		case Opt_inode64:
			mp->m_flags &= ~XFS_MOUNT_SMALL_INUMS;
			mp->m_maxagi = xfs_set_inode_alloc(mp, sbp->sb_agcount);
			break;
		case Opt_inode32:
			mp->m_flags |= XFS_MOUNT_SMALL_INUMS;
			mp->m_maxagi = xfs_set_inode_alloc(mp, sbp->sb_agcount);
			break;
		default:


#if 0
			xfs_info(mp,
		"mount option \"%s\" not supported for remount", p);
			return -EINVAL;
#else
			break;
#endif
		}
	}


	if ((mp->m_flags & XFS_MOUNT_RDONLY) && !(*flags & SB_RDONLY)) {
		if (mp->m_flags & XFS_MOUNT_NORECOVERY) {
			xfs_warn(mp,
		"ro->rw transition prohibited on norecovery mount");
			return -EINVAL;
		}

		if (XFS_SB_VERSION_NUM(sbp) == XFS_SB_VERSION_5 &&
		    xfs_sb_has_ro_compat_feature(sbp,
					XFS_SB_FEAT_RO_COMPAT_UNKNOWN)) {
			xfs_warn(mp,
"ro->rw transition prohibited on unknown (0x%x) ro-compat filesystem",
				(sbp->sb_features_ro_compat &
					XFS_SB_FEAT_RO_COMPAT_UNKNOWN));
			return -EINVAL;
		}

		mp->m_flags &= ~XFS_MOUNT_RDONLY;


		if (mp->m_update_sb) {
			error = xfs_sync_sb(mp, false);
			if (error) {
				xfs_warn(mp, "failed to write sb changes");
				return error;
			}
			mp->m_update_sb = false;
		}


		xfs_restore_resvblks(mp);
		xfs_log_work_queue(mp);


		error = xfs_reflink_recover_cow(mp);
		if (error) {
			xfs_err(mp,
	"Error %d recovering leftover CoW allocations.", error);
			xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
			return error;
		}
		xfs_icache_enable_reclaim(mp);


		error = xfs_fs_reserve_ag_blocks(mp);
		if (error && error != -ENOSPC)
			return error;
	}


	if (!(mp->m_flags & XFS_MOUNT_RDONLY) && (*flags & SB_RDONLY)) {


		xfs_icache_disable_reclaim(mp);


		error = xfs_icache_free_cowblocks(mp, NULL);
		if (error) {
			xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
			return error;
		}


		error = xfs_fs_unreserve_ag_blocks(mp);
		if (error) {
			xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
			return error;
		}


		xfs_save_resvblks(mp);

		xfs_quiesce_attr(mp);
		mp->m_flags |= XFS_MOUNT_RDONLY;
	}

	return 0;
}
