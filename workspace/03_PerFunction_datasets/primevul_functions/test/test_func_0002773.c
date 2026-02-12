Status MutableGraphView::UpdateFanoutsInternal(NodeDef* from_node,
                                               NodeDef* to_node) {
  VLOG(2) << absl::Substitute("Update fanouts from '$0' to '$1'.",
                              from_node->name(), to_node->name());
  if (from_node == to_node) {
    return Status::OK();
  }


  const auto add_edge = [this](const OutputPort& output_port,
                               const InputPort& input_port) {
    fanouts()[output_port].insert(input_port);
  };


  const auto remove_edge = [this](const OutputPort& output_port,
                                  const InputPort& input_port) {
    fanouts()[output_port].erase(input_port);
  };


  auto control_fanouts =
      GetFanout(GraphView::OutputPort(from_node, Graph::kControlSlot));

  bool to_node_is_switch = IsSwitch(*to_node);
  for (const InputPort& control_port : control_fanouts) {

    if (control_port.node == to_node) continue;


    if (to_node_is_switch) {


      return UpdateFanoutsError(from_node->name(), to_node->name())(
          absl::Substitute("can't update fanouts to node '$0' as it will "
                           "become a Switch control dependency",
                           to_node->name()));
    }

    NodeDef* node = control_port.node;
    RemoveControllingFaninInternal(node, from_node);
    AddFaninInternal(node, {to_node, Graph::kControlSlot});
  }


  auto regular_edges =
      GetFanoutEdges(*from_node, false);


  int keep_max_regular_output_port = -1;

  for (const Edge& edge : regular_edges) {
    const OutputPort output_port = edge.src;
    const InputPort input_port = edge.dst;


    if (input_port.node == to_node) {
      keep_max_regular_output_port =
          std::max(keep_max_regular_output_port, output_port.port_id);
      continue;
    }


    input_port.node->set_input(
        input_port.port_id,
        TensorIdToString({to_node->name(), output_port.port_id}));


    remove_edge(output_port, input_port);

    add_edge(OutputPort(to_node, output_port.port_id), input_port);

    if (CanDedupControlWithRegularInput(*this, *to_node)) {
      RemoveControllingFaninInternal(input_port.node, to_node);
    }
  }


  max_regular_output_port()[to_node] = max_regular_output_port()[from_node];


  if (keep_max_regular_output_port >= 0) {
    max_regular_output_port()[from_node] = keep_max_regular_output_port;
  } else {
    max_regular_output_port().erase(from_node);
  }

  return Status::OK();
}
