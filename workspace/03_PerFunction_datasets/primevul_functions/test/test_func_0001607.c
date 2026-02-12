Status DependencyOptimizer::TransitiveReduction() {

  const int num_nodes = optimized_graph_->node_size();


  int num_controls = 0;
  std::vector<std::vector<int>> outputs(num_nodes);
  std::vector<gtl::InlinedVector<std::pair<int, int>, 2>> control_outputs(
      num_nodes);


  std::vector<std::pair<int, int>> target_range(num_nodes, {num_nodes, -1});
  for (int node_idx = 0; node_idx < num_nodes; ++node_idx) {
    const NodeDef& node = optimized_graph_->node(node_idx);
    if (ModifiesFrameInfo(node) || !HasOpDef(node)) {

      continue;
    }
    for (int input_slot = 0; input_slot < node.input_size(); ++input_slot) {
      const string& input = node.input(input_slot);
      const NodeDef* input_node = node_map_->GetNode(input);
      if (ModifiesFrameInfo(*input_node) || IsMerge(*input_node)) {


        continue;
      }
      const int input_node_idx = node_to_idx_[input_node];
      outputs[input_node_idx].push_back(node_idx);
      target_range[input_node_idx].first =
          std::min(target_range[input_node_idx].first, node_idx);
      if (IsControlInput(input)) {
        ++num_controls;
        control_outputs[input_node_idx].emplace_back(node_idx, input_slot);
        target_range[input_node_idx].second =
            std::max(target_range[input_node_idx].second, node_idx);
      }
    }
  }


  int num_controls_removed = 0;
  std::vector<DistanceFromSource> longest_distance(num_nodes);


  typedef std::pair<int, int> InputSlotAndSource;
  absl::flat_hash_map<
      int, std::set<InputSlotAndSource, std::greater<InputSlotAndSource>>>
      control_edges_to_remove;
  for (int source = 0; source < num_nodes; ++source) {
    if (target_range[source].first >= target_range[source].second ||
        target_range[source].second <= source) {
      continue;
    }


    std::fill(longest_distance.begin() + target_range[source].first,
              longest_distance.begin() + target_range[source].second + 1, ZERO);
    LongestPathsLowerBounds(source, target_range[source], outputs,
                            &longest_distance);


    for (const auto& control_output : control_outputs[source]) {
      const int target = control_output.first;
      if (longest_distance[target] == TWO_OR_GREATER) {
        const int input_slot = control_output.second;
        control_edges_to_remove[target].emplace(input_slot, source);
      }
    }
  }
  for (const auto& it : control_edges_to_remove) {
    const int target = it.first;
    NodeDef* target_node = optimized_graph_->mutable_node(target);
    for (const InputSlotAndSource& slot_and_source : it.second) {
      const int input_slot = slot_and_source.first;
      const int source = slot_and_source.second;
      const NodeDef& source_node = optimized_graph_->node(source);
      CHECK_LT(input_slot, target_node->input_size());
      target_node->mutable_input()->SwapElements(input_slot,
                                                 target_node->input_size() - 1);
      node_map_->RemoveOutput(source_node.name(), target_node->name());
      target_node->mutable_input()->RemoveLast();
      ++num_controls_removed;
    }
  }
  VLOG(1) << "Removed " << num_controls_removed << " out of " << num_controls
          << " control dependencies";
  return Status::OK();
}
