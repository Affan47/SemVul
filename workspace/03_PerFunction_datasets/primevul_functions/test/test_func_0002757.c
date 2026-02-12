bool MutableGraphView::RemoveRegularFaninInternal(NodeDef* node,
                                                  const OutputPort& fanin) {
  auto remove_input = [this, node](const OutputPort& fanin_port,
                                   int node_input_port, bool update_max_port) {
    InputPort input(node, node_input_port);

    absl::flat_hash_set<InputPort>* fanouts_set = &fanouts()[fanin_port];
    fanouts_set->erase(input);
    if (update_max_port) {
      UpdateMaxRegularOutputPortForRemovedFanin(fanin_port, *fanouts_set);
    }
    return fanouts_set;
  };

  auto mutable_inputs = node->mutable_input();
  bool modified = false;
  const int num_regular_fanins =
      NumFanins(*node, false);
  int i;
  int curr_pos = 0;
  for (i = 0; i < num_regular_fanins; ++i) {
    TensorId tensor_id = ParseTensorName(node->input(i));
    if (tensor_id.node() == fanin.node->name() &&
        tensor_id.index() == fanin.port_id) {
      remove_input(fanin, i, true);
      modified = true;
    } else if (modified) {

      OutputPort fanin_port(nodes()[tensor_id.node()], tensor_id.index());
      auto fanouts_set = remove_input(fanin_port, i, false);
      fanouts_set->insert({node, curr_pos});

      mutable_inputs->SwapElements(i, curr_pos);
      ++curr_pos;
    } else {

      ++curr_pos;
    }
  }

  if (modified) {
    const int last_regular_input_port = curr_pos - 1;
    if (last_regular_input_port < 0) {
      max_regular_input_port().erase(node);
    } else {
      max_regular_input_port()[node] = last_regular_input_port;
    }
    if (curr_pos < i) {

      mutable_inputs->DeleteSubrange(curr_pos, i - curr_pos);
    }
  }

  return modified;
}
