gt_region_mapping_get_md5_fingerprint(GtRegionMapping *rm,
                                                  GtStr *seqid,
                                                  const GtRange *range,
                                                  unsigned long *offset,
                                                  GtError *err)
{
  const char *md5 = NULL;
  int had_err;
  unsigned long filenum, seqnum;
  gt_error_check(err);
  gt_assert(rm && seqid);
  gt_assert(!rm->userawseq);
  gt_assert(!gt_md5_seqid_has_prefix(gt_str_get(seqid)));
  had_err = update_seq_col_if_necessary(rm, seqid, err);
  if (!had_err) {
    if (rm->usedesc) {
      gt_assert(rm->seqid2seqnum_mapping);
      had_err = gt_seqid2seqnum_mapping_map(rm->seqid2seqnum_mapping,
                                            gt_str_get(seqid), range, &seqnum,
                                            &filenum,
                                            offset, err);
      if (!had_err)
        md5 = gt_seq_col_get_md5_fingerprint(rm->seq_col, filenum, seqnum);
    }
    else if (rm->matchdesc) {
      if (!rm->seq_col) {
        if (rm->encseq) {
          if (!(rm->seq_col = gt_encseq_col_new(rm->encseq, err)))
            had_err = -1;
        } else {
          if (!(rm->seq_col = gt_bioseq_col_new(rm->sequence_filenames, err)))
            had_err = -1;
        }
      }
      if (!had_err)
        had_err = gt_seq_col_grep_desc_md5(rm->seq_col, &md5, seqid, err);
      *offset = 1;
    }
    else {
      if (!had_err)
        md5 = gt_seq_col_get_md5_fingerprint(rm->seq_col, 0, 0);
      *offset = 1;
    }
  }
  return md5;
}
