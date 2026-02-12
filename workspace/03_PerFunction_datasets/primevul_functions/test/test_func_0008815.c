static int split_compressed_hole(ntfs_attr *na, runlist_element **prl,
    		s64 pos, s64 count, VCN *update_from)
{
	int compressed_part;
	int cluster_size_bits = na->ni->vol->cluster_size_bits;
	runlist_element *rl = *prl;

	compressed_part
		= na->compression_block_clusters;

	if (rl->length > na->compression_block_clusters) {
		*prl = ntfs_rl_extend(na,*prl,2);
		if (!*prl) {
			compressed_part = -1;
		} else {
			rl = *prl;
			na->unused_runs = 2;
		}
	}
	if (*prl && (rl->length > na->compression_block_clusters)) {


		int beginwrite = (pos >> cluster_size_bits) - rl->vcn;
		s32 endblock = (((pos + count - 1) >> cluster_size_bits)
			| (na->compression_block_clusters - 1)) + 1 - rl->vcn;

		compressed_part = na->compression_block_clusters
			- (rl->length & (na->compression_block_clusters - 1));
		if ((beginwrite + compressed_part) >= na->compression_block_clusters)
			compressed_part = na->compression_block_clusters;


		if (endblock < rl[0].length) {
			runlist_element *xrl;
			int n;


			if (endblock > na->compression_block_clusters) {
				if (na->unused_runs < 2) {
ntfs_log_error("No free run, case 1\n");
				}
				na->unused_runs -= 2;
				xrl = rl;
				n = 0;
				while (xrl->length) {
					xrl++;
					n++;
				}
				do {
					xrl[2] = *xrl;
					xrl--;
				} while (xrl != rl);
				rl[1].length = na->compression_block_clusters;
				rl[2].length = rl[0].length - endblock;
				rl[0].length = endblock
					- na->compression_block_clusters;
				rl[1].lcn = LCN_HOLE;
				rl[2].lcn = LCN_HOLE;
				rl[1].vcn = rl[0].vcn + rl[0].length;
				rl[2].vcn = rl[1].vcn
					+ na->compression_block_clusters;
				rl = ++(*prl);
			} else {


				if (!na->unused_runs) {
ntfs_log_error("No free run, case 2\n");
				}
				na->unused_runs--;
				xrl = rl;
				n = 0;
				while (xrl->length) {
					xrl++;
					n++;
				}
				do {
					xrl[1] = *xrl;
					xrl--;
				} while (xrl != rl);
				if (beginwrite < endblock) {

					rl[1].length = rl[0].length - endblock;
					rl[0].length = endblock;
					rl[1].vcn = rl[0].vcn + rl[0].length;
					rl[1].lcn = LCN_HOLE;
				} else {


					rl[1].length = rl[0].length - endblock;
					rl[0].length = endblock;
					rl[1].vcn = rl[0].vcn + rl[0].length;
					rl[1].lcn = LCN_HOLE;
					rl = ++(*prl);
				}
			}
		} else {
			if (rl[1].length) {
				runlist_element *xrl;
				int n;


				if (!na->unused_runs) {
ntfs_log_error("No free run, case 4\n");
				}
				na->unused_runs--;
				xrl = rl;
				n = 0;
				while (xrl->length) {
					xrl++;
					n++;
				}
				do {
					xrl[1] = *xrl;
					xrl--;
				} while (xrl != rl);
			} else {
				rl[2].lcn = rl[1].lcn;
				rl[2].vcn = rl[1].vcn;
				rl[2].length = rl[1].length;
			}
			rl[1].vcn -= na->compression_block_clusters;
			rl[1].lcn = LCN_HOLE;
			rl[1].length = na->compression_block_clusters;
			rl[0].length -= na->compression_block_clusters;
			if (pos >= (rl[1].vcn << cluster_size_bits)) {
				rl = ++(*prl);
			}
		}
	NAttrSetRunlistDirty(na);
	if ((*update_from == -1) || ((*prl)->vcn < *update_from))
		*update_from = (*prl)->vcn;
	}
	return (compressed_part);
}
