xfs_qm_reset_dqcounts(
	xfs_mount_t	*mp,
	xfs_buf_t	*bp,
	xfs_dqid_t	id,
	uint		type)
{
	struct xfs_dqblk	*dqb;
	int			j;

	trace_xfs_reset_dqcounts(bp, _RET_IP_);


#ifdef DEBUG
	j = XFS_FSB_TO_B(mp, XFS_DQUOT_CLUSTER_SIZE_FSB);
	do_div(j, sizeof(xfs_dqblk_t));
	ASSERT(mp->m_quotainfo->qi_dqperchunk == j);
#endif
	dqb = bp->b_addr;
	for (j = 0; j < mp->m_quotainfo->qi_dqperchunk; j++) {
		struct xfs_disk_dquot	*ddq;

		ddq = (struct xfs_disk_dquot *)&dqb[j];


		xfs_dqcheck(mp, ddq, id+j, type, XFS_QMOPT_DQREPAIR,
			    "xfs_quotacheck");


		ddq->d_flags = type;
		ddq->d_bcount = 0;
		ddq->d_icount = 0;
		ddq->d_rtbcount = 0;
		ddq->d_btimer = 0;
		ddq->d_itimer = 0;
		ddq->d_rtbtimer = 0;
		ddq->d_bwarns = 0;
		ddq->d_iwarns = 0;
		ddq->d_rtbwarns = 0;

		if (xfs_sb_version_hascrc(&mp->m_sb)) {
			xfs_update_cksum((char *)&dqb[j],
					 sizeof(struct xfs_dqblk),
					 XFS_DQUOT_CRC_OFF);
		}
	}
}
