void Graph::Copy(const Graph& src) {
  SetConstructionContext(src.GetConstructionContextInternal());
  for (Node* n : nodes()) {
    CHECK(n->IsSource() || n->IsSink()) << "*dest must be empty";
  }


  set_versions(src.versions());


  gtl::FlatMap<const Node*, Node*> node_map;
  node_map.reserve(src.num_nodes());
  node_map[src.source_node()] = source_node();
  node_map[src.sink_node()] = sink_node();
  for (Node* n : src.op_nodes()) {
    auto copy = CopyNode(n);
    copy->in_edges_.reserve(n->in_edges().size());
    copy->out_edges_.reserve(n->out_edges().size());
    node_map[n] = copy;
  }


  edges_.reserve(src.num_edges());
  for (const Edge* e : src.edges()) {
    Node* src_copy = node_map[e->src()];
    Node* dst_copy = node_map[e->dst()];
    AddEdge(src_copy, e->src_output(), dst_copy, e->dst_input());
  }
}
