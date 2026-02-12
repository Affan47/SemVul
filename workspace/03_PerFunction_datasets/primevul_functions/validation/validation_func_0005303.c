void CopyGraph(const Graph& src, Graph* dest) {
  dest->SetConstructionContext(src.GetConstructionContextInternal());

  for (Node* n : dest->nodes()) {
    CHECK(n->IsSource() || n->IsSink()) << "*dest must be empty";
  }


  dest->set_versions(src.versions());


  gtl::FlatMap<const Node*, Node*> node_map;
  node_map[src.source_node()] = dest->source_node();
  node_map[src.sink_node()] = dest->sink_node();
  for (Node* n : src.op_nodes()) {
    node_map[n] = dest->CopyNode(n);
  }


  for (const Edge* e : src.edges()) {
    Node* src_copy = node_map[e->src()];
    Node* dst_copy = node_map[e->dst()];
    dest->AddEdge(src_copy, e->src_output(), dst_copy, e->dst_input());
  }
}
