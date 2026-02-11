xfs_agfl_verify(
	struct xfs_buf	*bp)
{
	struct xfs_mount *mp = bp->b_target->bt_mount;
	struct xfs_agfl	*agfl = XFS_BUF_TO_AGFL(bp);
	int		i;

	if (!uuid_equal(&agfl->agfl_uuid, &mp->m_sb.sb_meta_uuid))
		return false;
	if (be32_to_cpu(agfl->agfl_magicnum) != XFS_AGFL_MAGIC)
		return false;


	if (bp->b_pag && be32_to_cpu(agfl->agfl_seqno) != bp->b_pag->pag_agno)
		return false;

	for (i = 0; i < XFS_AGFL_SIZE(mp); i++) {
		if (be32_to_cpu(agfl->agfl_bno[i]) != NULLAGBLOCK &&
		    be32_to_cpu(agfl->agfl_bno[i]) >= mp->m_sb.sb_agblocks)
			return false;
	}

	return xfs_log_check_lsn(mp,
				 be64_to_cpu(XFS_BUF_TO_AGFL(bp)->agfl_lsn));
}
