bool ConstantFolding::SimplifySwitch(GraphDef* optimized_graph, NodeDef* node) {
  if (node->op() == "Switch" && node->input(0) == node->input(1) &&
      !OptimizedNodeExists(*node, "_const_false") &&
      !OptimizedNodeExists(*node, "_const_true")) {
    bool already_optimized = true;


    const auto& fanouts = node_map_->GetOutputs(node->name());
    if (fanouts.size() == 2) {
      for (const NodeDef* fanout : fanouts) {
        if ((!IsIdentity(*fanout) && !IsIdentityNSingleInput(*fanout)) ||
            HasRegularOutputs(*fanout, *node_map_)) {
          already_optimized = false;
          break;
        }
      }
    }
    Tensor false_t(DT_BOOL, TensorShape({}));
    Tensor true_t(DT_BOOL, TensorShape({}));

    if (!already_optimized && SetTensorValue(DT_BOOL, true, &true_t).ok() &&
        SetTensorValue(DT_BOOL, false, &false_t).ok()) {


      std::vector<NodeDef*> consumers =
          node_map_->GetOutputsOrderedByNodeName(node->name());

      NodeDef tmp_false_node;
      tmp_false_node.set_name(OptimizedNodeName(*node, "_const_false"));
      if (!CreateNodeDef(tmp_false_node.name(), TensorValue(&false_t),
                         &tmp_false_node)
               .ok()) {
        return false;
      }
      tmp_false_node.set_device(node->device());
      NodeDef tmp_true_node;
      tmp_true_node.set_name(OptimizedNodeName(*node, "_const_true"));
      if (!CreateNodeDef(tmp_true_node.name(), TensorValue(&true_t),
                         &tmp_true_node)
               .ok()) {
        return false;
      }
      tmp_true_node.set_device(node->device());


      NodeDef* false_node = optimized_graph->add_node();
      false_node->Swap(&tmp_false_node);
      NodeDef* true_node = optimized_graph->add_node();
      true_node->Swap(&tmp_true_node);


      const string false_port = node->name();
      const string true_port = strings::StrCat(node->name(), ":1");
      const string false_ctrl_dep =
          AddControlDependency(false_port, optimized_graph, node_map_.get());
      false_node->add_input(false_ctrl_dep);
      const string true_ctrl_dep =
          AddControlDependency(true_port, optimized_graph, node_map_.get());
      true_node->add_input(true_ctrl_dep);

      node_map_->AddNode(false_node->name(), false_node);
      node_map_->AddNode(true_node->name(), true_node);
      node_map_->AddOutput(NodeName(false_ctrl_dep), false_node->name());
      node_map_->AddOutput(NodeName(true_ctrl_dep), true_node->name());

      for (NodeDef* consumer : consumers) {
        for (int i = 0; i < consumer->input_size(); ++i) {
          const string& input = consumer->input(i);
          if (input == false_port) {
            consumer->set_input(i, false_node->name());
            node_map_->UpdateInput(consumer->name(), false_port,
                                   false_node->name());
          } else if (input == true_port) {
            consumer->set_input(i, true_node->name());
            node_map_->UpdateInput(consumer->name(), true_port,
                                   true_node->name());
          }
        }
      }
      return true;
    }
  }
  return false;
}
