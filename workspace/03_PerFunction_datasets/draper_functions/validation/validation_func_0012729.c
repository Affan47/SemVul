pbs_attach_results_to_gff3(GtPBSResults *results,
                                       GtLTRElement *element,
                                       GtStrand *canonical_strand,
                                       GtStr *tag)
{
  GtRange pbs_range;
  GtGenomeNode *gf;
  unsigned long i = 0;
  char buffer[BUFSIZ];
  GtPBSHit* hit = gt_pbs_results_get_ranked_hit(results, i++);
  if (*canonical_strand == GT_STRAND_UNKNOWN)
    *canonical_strand = gt_pbs_hit_get_strand(hit);
  else
  {


    while (gt_pbs_hit_get_strand(hit) != *canonical_strand
             && i < gt_pbs_results_get_number_of_hits(results))
    {
      gt_log_log("dropping PBS because of nonconsistent strand: %s\n",
                 gt_feature_node_get_attribute(element->mainnode, "ID"));
      hit = gt_pbs_results_get_ranked_hit(results, i++);
    }

    if (gt_pbs_hit_get_strand(hit) != *canonical_strand)
      return;
  }
  pbs_range = gt_pbs_hit_get_coords(hit);
  pbs_range.start++; pbs_range.end++;
  gf = gt_feature_node_new(gt_genome_node_get_seqid((GtGenomeNode*)
                                                    element->mainnode),
                           gt_ft_primer_binding_site,
                           pbs_range.start,
                           pbs_range.end,
                           gt_pbs_hit_get_strand(hit));
  gt_feature_node_set_source((GtFeatureNode*) gf, tag);
  gt_feature_node_set_score((GtFeatureNode*) gf,
                            (float) gt_pbs_hit_get_score(hit));
  if (gt_pbs_hit_get_trna(hit) != NULL) {
    gt_feature_node_add_attribute((GtFeatureNode*) gf, "trna",
                                   gt_pbs_hit_get_trna(hit));
  }
  gt_feature_node_set_strand(element->mainnode, gt_pbs_hit_get_strand(hit));
  (void) snprintf(buffer, BUFSIZ-1, "%lu", gt_pbs_hit_get_tstart(hit));
  gt_feature_node_add_attribute((GtFeatureNode*) gf, "trnaoffset", buffer);
  (void) snprintf(buffer, BUFSIZ-1, "%lu", gt_pbs_hit_get_offset(hit));
  gt_feature_node_add_attribute((GtFeatureNode*) gf, "pbsoffset", buffer);
  (void) snprintf(buffer, BUFSIZ-1, "%lu", gt_pbs_hit_get_edist(hit));
  gt_feature_node_add_attribute((GtFeatureNode*) gf, "edist", buffer);
  gt_feature_node_add_child(element->mainnode, (GtFeatureNode*) gf);
}
