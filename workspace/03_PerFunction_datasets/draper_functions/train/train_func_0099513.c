xlog_recover_ra_pass2(
	struct xlog			*log,
	struct xlog_recover_item	*item)
{
	switch (ITEM_TYPE(item)) {
	case XFS_LI_BUF:
		xlog_recover_buffer_ra_pass2(log, item);
		break;
	case XFS_LI_INODE:
		xlog_recover_inode_ra_pass2(log, item);
		break;
	case XFS_LI_DQUOT:
		xlog_recover_dquot_ra_pass2(log, item);
		break;
	case XFS_LI_EFI:
	case XFS_LI_EFD:
	case XFS_LI_QUOTAOFF:
	default:
		break;
	}
}
