bool ConstantFolding::SimplifyPack(GraphDef* optimized_graph, NodeDef* node) {
  const string axis_node_name = OptimizedNodeName(*node, "_const_axis");
  if (!IsPack(*node) || NumNonControlInputs(*node) != 1 ||
      node_map_->NodeExists(axis_node_name)) {
    return false;
  }


  if (feed_nodes_.find(NodeName(node->input(0))) != feed_nodes_.end()) {
    return false;
  }


  Tensor axis_t(DT_INT32, TensorShape({}));
  const int axis =
      node->attr().count("axis") == 0 ? 0 : node->attr().at("axis").i();
  NodeDef new_node;
  if (!SetTensorValue(DT_INT32, axis, &axis_t).ok() ||
      !CreateNodeDef(axis_node_name, TensorValue(&axis_t), &new_node).ok()) {
    return false;
  }
  NodeDef* axis_node = optimized_graph->add_node();
  *axis_node = std::move(new_node);
  axis_node->set_name(axis_node_name);
  node_map_->AddNode(axis_node->name(), axis_node);

  const string ctrl_dep = ConstantFolding::AddControlDependency(
      node->input(0), optimized_graph, node_map_.get());
  axis_node->add_input(ctrl_dep);
  axis_node->set_device(node->device());
  node_map_->AddOutput(NodeName(node->input(0)), axis_node->name());
  node->set_op("ExpandDims");
  if (node->attr().count("axis") != 0) {
    node->mutable_attr()->erase("axis");
  }
  if (node->attr().count("N") != 0) {
    node->mutable_attr()->erase("N");
  }
  (*node->mutable_attr())["Tdim"].set_type(DT_INT32);
  node->add_input(axis_node->name());
  node_map_->AddOutput(axis_node->name(), node->name());
  if (node->input_size() > 2) {
    node->mutable_input()->SwapElements(1, node->input_size() - 1);
  }
  return true;
}
