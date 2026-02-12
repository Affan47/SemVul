Status MutableGraphView::DeleteNodes(
    const absl::flat_hash_set<string>& nodes_to_delete) {
  TF_RETURN_IF_ERROR(CheckNodesCanBeDeleted(nodes_to_delete));


  for (const string& node_name_to_delete : nodes_to_delete) {
    NodeDef* node = GetNode(node_name_to_delete);
    if (node != nullptr) {
      RemoveFaninsInternal(node, false);
      RemoveFanoutsInternal(node);
    }
  }
  for (const string& node_name_to_delete : nodes_to_delete) {
    nodes().erase(node_name_to_delete);
  }


  int pos = 0;
  const int last_idx = graph()->node_size() - 1;
  int last_pos = last_idx;
  while (pos <= last_pos) {
    if (nodes_to_delete.contains(graph()->node(pos).name())) {
      graph()->mutable_node()->SwapElements(pos, last_pos);
      --last_pos;
    } else {
      ++pos;
    }
  }
  if (last_pos < last_idx) {
    graph()->mutable_node()->DeleteSubrange(last_pos + 1, last_idx - last_pos);
  }

  return Status::OK();
}
