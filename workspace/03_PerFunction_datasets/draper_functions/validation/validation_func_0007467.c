run_ltrdigest(GtLTRElement *element, char *seq,
                         GtLTRdigestStream *ls,
#ifdef HAVE_HMMER
                         GtError *err)
#else
                         GT_UNUSED GtError *err)
#endif
{
  int had_err = 0;
  char *rev_seq;
  unsigned long seqlen = gt_ltrelement_length(element);
  GtStrand canonical_strand = GT_STRAND_UNKNOWN;


  rev_seq = gt_calloc((size_t) seqlen+1, sizeof (char));
  memcpy(rev_seq, seq, sizeof (char) * seqlen);
  had_err = gt_reverse_complement(rev_seq, seqlen, err);

  if (!had_err)
  {
#ifdef HAVE_HMMER


    if (ls->tests_to_run & GT_LTRDIGEST_RUN_PDOM)
    {
      GtPdomResults *pdom_results = NULL;
      if (!ls->pdf)
      {
        gt_error_set(err, "No PdomFinder object found -- "
                          "how could that happen?");
        had_err = -1;
      } else
      {
        pdom_results = gt_pdom_finder_find(ls->pdf, (const char*) seq,
                                           (const char*) rev_seq, element, err);
        if (!pdom_results)
        {
          had_err = -1;
        } else {
          if (pdom_results && !gt_pdom_results_empty(pdom_results))
          {

            if (gt_double_compare(
                     gt_pdom_results_get_combined_evalue_fwd(pdom_results),
                     gt_pdom_results_get_combined_evalue_rev(pdom_results)) < 0)
              canonical_strand = GT_STRAND_FORWARD;
            else
              canonical_strand = GT_STRAND_REVERSE;
            gt_feature_node_set_strand(ls->element.mainnode, canonical_strand);

            (void) gt_pdom_results_foreach_domain_hit(pdom_results,
                                                      pdom_hit_attach_gff3,
                                                      ls,
                                                      err);
          }
          gt_pdom_results_delete(pdom_results);
        }
      }
    }
#endif


    if (ls->tests_to_run & GT_LTRDIGEST_RUN_PPT)
    {
      GtPPTResults *ppt_results = NULL;
      ppt_results = gt_ppt_find((const char*) seq, (const char*) rev_seq,
                              element, ls->ppt_opts);
      if (gt_ppt_results_get_number_of_hits(ppt_results) > 0)
      {
        ppt_attach_results_to_gff3(ppt_results, element, &canonical_strand,
                                   ls->ltrdigest_tag);
      }
      gt_ppt_results_delete(ppt_results);
    }


    if (ls->tests_to_run & GT_LTRDIGEST_RUN_PBS)
    {
      GtPBSResults *pbs_results = NULL;
      pbs_results = gt_pbs_find((const char*) seq, (const char*) rev_seq,
                                element, ls->pbs_opts, err);
       if (gt_pbs_results_get_number_of_hits(pbs_results) > 0)
       {
        pbs_attach_results_to_gff3(pbs_results, element, &canonical_strand,
                                   ls->ltrdigest_tag);
       }
       gt_pbs_results_delete(pbs_results);
    }
  }
  gt_free(rev_seq);
  return had_err;
}
