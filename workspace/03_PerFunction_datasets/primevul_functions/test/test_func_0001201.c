bool ConstantFolding::MergeConcat(bool use_shape_info,
                                  GraphProperties* properties,
                                  GraphDef* optimized_graph, NodeDef* node) {

  int axis;
  if (!use_shape_info || !GetConcatAxis(*node, &axis) ||
      nodes_to_preserve_.find(node->name()) != nodes_to_preserve_.end() ||
      node_map_->GetOutputs(node->name()).size() != 1) {
    return false;
  }


  const int num_regular_inputs = NumNonControlInputs(*node);
  bool all_inputs_are_const = true;
  for (int i = 0; i < num_regular_inputs - 1; ++i) {
    const NodeDef* input_node = node_map_->GetNode(node->input(i));
    if (!IsReallyConstant(*input_node)) {
      all_inputs_are_const = false;
      break;
    }
  }
  if (all_inputs_are_const) return false;

  NodeDef* parent = *node_map_->GetOutputs(node->name()).begin();
  int parent_axis;
  if (!GetConcatAxis(*parent, &parent_axis) || axis != parent_axis) {
    return false;
  }


  string task, device;
  absl::flat_hash_set<string> unique_input_tasks;
  const int n_parent_inputs = NumNonControlInputs(*parent);


  for (int i = 0; i < n_parent_inputs - 1; ++i) {
    const NodeDef* input_node = node_map_->GetNode(parent->input(i));
    if (!input_node->device().empty() &&
        tensorflow::DeviceNameUtils::SplitDeviceName(input_node->device(),
                                                     &task, &device)) {
      unique_input_tasks.insert(task);
      if (unique_input_tasks.size() >= 2) {


        return false;
      }
    }
  }

  protobuf::RepeatedPtrField<string> parent_inputs;
  parent_inputs.Swap(parent->mutable_input());


  for (const auto& input : parent_inputs) {
    if (IsSameInput(input, node->name())) {
      for (int j = 0; j < num_regular_inputs - 1; ++j) {


        parent->add_input(node->input(j));
        node_map_->UpdateInput(parent->name(), node->name(), node->input(j));
      }
    } else {
      parent->add_input(input);
    }
  }

  const int num_inputs = node->input_size();
  for (int i = num_inputs - 1; i >= num_regular_inputs; --i) {
    parent->add_input(node->input(i));
    node_map_->UpdateInput(parent->name(), node->name(), node->input(i));
    node->mutable_input()->RemoveLast();
  }
  (*parent->mutable_attr())["N"].set_i(NumNonControlInputs(*parent) - 1);
  DedupControlInputs(parent);
  ReplaceOperationWithNoOp(node, properties, optimized_graph);

  return true;
}
