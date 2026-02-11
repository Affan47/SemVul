add_ids_visitor_comment_node(GtNodeVisitor *nv, GtCommentNode *c,
                                        GT_UNUSED GtError *err)
{
  GtAddIDsVisitor *add_ids_visitor;
  gt_error_check(err);
  add_ids_visitor = add_ids_visitor_cast(nv);
  gt_queue_add(add_ids_visitor->node_buffer, c);
  return 0;
}
