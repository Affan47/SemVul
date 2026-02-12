bool ConstantFolding::PartialAssocOpConstFolding(GraphDef* optimized_graph,
                                                 GraphProperties* properties,
                                                 NodeDef* node) {


  if (!IsAggregate(*node) || !IsCommutative(*node)) return false;

  const int num_non_control_inputs = NumNonControlInputs(*node);
  if (num_non_control_inputs <= 2) return false;
  const int num_control_inputs = node->input_size() - num_non_control_inputs;
  std::vector<int> const_inputs;
  std::vector<int> nonconst_inputs;
  for (int i = 0; i < node->input_size(); ++i) {
    const string& input = node->input(i);
    const NodeDef* input_node = node_map_->GetNode(NodeName(input));
    if (input_node == nullptr) return false;
    if (!IsControlInput(input) && IsReallyConstant(*input_node)) {
      const_inputs.push_back(i);
    } else {

      nonconst_inputs.push_back(i);
    }
  }


  int const_inputs_size = const_inputs.size();
  if (const_inputs_size == num_non_control_inputs &&
      node->op() == "AccumulateNV2") {
    node->set_op("AddN");
    node->mutable_attr()->erase("shape");
    return true;
  }
  const string new_node_name = OptimizedNodeName(
      *node, strings::StrCat("_partial_split_", const_inputs_size));
  if (const_inputs_size > 1 && const_inputs_size < num_non_control_inputs &&
      !node_map_->NodeExists(new_node_name)) {
    NodeDef* added_node = optimized_graph->add_node();
    *added_node = *node;


    added_node->set_op("AddN");
    added_node->mutable_attr()->erase("shape");
    added_node->set_name(new_node_name);
    node_map_->AddNode(added_node->name(), added_node);
    added_node->clear_input();
    for (int i : const_inputs) {
      added_node->add_input(node->input(i));
      node_map_->UpdateOutput(NodeName(node->input(i)), node->name(),
                              added_node->name());
    }


    node->set_input(const_inputs[0], added_node->name());
    node_map_->AddOutput(added_node->name(), node->name());
    nonconst_inputs.push_back(const_inputs[0]);

    std::sort(nonconst_inputs.begin(), nonconst_inputs.end());
    int idx = 0;
    for (int i : nonconst_inputs) {
      if (idx != i) {
        node->set_input(idx, node->input(i));
      }
      ++idx;
    }
    node->mutable_input()->DeleteSubrange(nonconst_inputs.size(),
                                          const_inputs.size() - 1);
    (*node->mutable_attr())["N"].set_i(node->input_size() - num_control_inputs);
    properties->ClearInputProperties(node->name());
    (*added_node->mutable_attr())["N"].set_i(const_inputs.size());
    return true;
  }
  return false;
}
