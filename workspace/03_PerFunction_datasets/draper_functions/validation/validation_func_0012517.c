gff3_visitor_free(GtNodeVisitor *nv)
{
  GtGFF3Visitor *gff3_visitor = gff3_visitor_cast(nv);
  gt_assert(gff3_visitor);
  gt_string_distri_delete(gff3_visitor->id_counter);
  gt_hashmap_delete(gff3_visitor->feature_node_to_id_array);
  gt_hashmap_delete(gff3_visitor->feature_node_to_unique_id_str);
  gt_cstr_table_delete(gff3_visitor->used_ids);
}
