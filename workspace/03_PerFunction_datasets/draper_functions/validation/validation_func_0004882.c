gt_feature_index_gfflike_get_features_for_seqid(GtFeatureIndex *gfi,
                                                         const char *seqid,
                                                         GtError *err)
{
  GtArray *a;
  GtFeatureIndexGFFlike *fi;
  GtRDBStmt *stmt;
  gt_assert(gfi && seqid);
  gt_error_check(err);
  fi = feature_index_gfflike_cast(gfi);
  stmt = fi->stmts[GT_PSTMT_GET_BY_SEQID_SELECT];
  a = gt_array_new(sizeof (GtFeatureNode*));
  gt_rdb_stmt_reset(stmt, err);
  gt_rdb_stmt_bind_string(stmt, 0, seqid, err);
  get_nodes_for_stmt(fi, a, stmt, err);
  return a;
}
