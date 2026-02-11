xfs_attr_rmtval_copyout(
	struct xfs_mount *mp,
	struct xfs_buf	*bp,
	xfs_ino_t	ino,
	int		*offset,
	int		*valuelen,
	__uint8_t	**dst)
{
	char		*src = bp->b_addr;
	xfs_daddr_t	bno = bp->b_bn;
	int		len = BBTOB(bp->b_length);
	int		blksize = mp->m_attr_geo->blksize;

	ASSERT(len >= blksize);

	while (len > 0 && *valuelen > 0) {
		int hdr_size = 0;
		int byte_cnt = XFS_ATTR3_RMT_BUF_SPACE(mp, blksize);

		byte_cnt = min(*valuelen, byte_cnt);

		if (xfs_sb_version_hascrc(&mp->m_sb)) {
			if (!xfs_attr3_rmt_hdr_ok(src, ino, *offset,
						  byte_cnt, bno)) {
				xfs_alert(mp,
"remote attribute header mismatch bno/off/len/owner (0x%llx/0x%x/Ox%x/0x%llx)",
					bno, *offset, byte_cnt, ino);
				return -EFSCORRUPTED;
			}
			hdr_size = sizeof(struct xfs_attr3_rmt_hdr);
		}

		memcpy(*dst, src + hdr_size, byte_cnt);


		len -= blksize;
		src += blksize;
		bno += BTOBB(blksize);


		*valuelen -= byte_cnt;
		*dst += byte_cnt;
		*offset += byte_cnt;
	}
	return 0;
}
