Status DependencyOptimizer::Optimize(Cluster* cluster, const GrapplerItem& item,
                                     GraphDef* optimized_graph) {
  optimized_graph_ = optimized_graph;
  *optimized_graph_ = item.graph;
  nodes_to_preserve_ = item.NodesToPreserve();
  fetch_nodes_known_ = !item.fetch.empty();
  CleanControlInputs();

  const int num_iterations = 2;
  for (int iteration = 0; iteration < num_iterations; ++iteration) {
    GRAPPLER_RETURN_IF_DEADLINE_EXCEEDED();
    Status topo_sort_status;

    topo_sort_status = TopologicalSort(optimized_graph_);

    node_map_.reset(new NodeMap(optimized_graph_));
    BuildNodeToIdx();

    if (topo_sort_status.ok()) {

      TF_RETURN_IF_ERROR(TransitiveReduction());
    } else {
      LOG(ERROR) << "Iteration = " << iteration
                 << ", topological sort failed with message: "
                 << topo_sort_status.error_message();
    }


    TF_RETURN_IF_ERROR(OptimizeDependencies());


    CleanControlInputs();


    GroupCrossDeviceControlEdges(false);


    GroupCrossDeviceControlEdges(true);
  }

  return Status::OK();
}
