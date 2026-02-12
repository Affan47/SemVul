Status ArithmeticOptimizer::Optimize(Cluster* ,
                                     const GrapplerItem& item,
                                     GraphDef* optimized_graph) {

  nodes_to_preserve_ = item.NodesToPreserve();
  fetch_nodes_known_ = !item.fetch.empty();
  GrapplerItem optimized_item(item);
  optimized_graph_ = &optimized_item.graph;

  node_map_.reset(new NodeMap(optimized_graph_));
  for (const auto& feed : item.feed) {
    feed_nodes_.insert(NodeName(feed.first));
  }


  options_.unary_ops_composition &=
      item.optimization_options().allow_non_differentiable_rewrites;


  TF_RETURN_IF_ERROR(TopologicalSort(optimized_graph_));
  GRAPPLER_RETURN_IF_DEADLINE_EXCEEDED();

  graph_properties_.reset(new GraphProperties(optimized_item));
  const bool assume_valid_feeds = opt_level_ == RewriterConfig::AGGRESSIVE;
  const Status status =
      graph_properties_->InferStatically(assume_valid_feeds,
                                         false,
                                         false);
  const bool can_use_shapes = status.ok();
  if (!can_use_shapes) {
    VLOG(1) << "Shape inference failed." << status.error_message();
  }


  TF_RETURN_IF_ERROR(SimplifyArithmeticOps(can_use_shapes));

  optimized_graph->Swap(optimized_graph_);
  return Status::OK();
}
