Status ConvertNodeDefsToGraph(const GraphConstructorOptions& opts,
                              gtl::ArraySlice<NodeDef> nodes, Graph* g) {
  ShapeRefiner refiner(TF_GRAPH_DEF_VERSION, g->op_registry());

  std::vector<const NodeDef*> node_defs;
  node_defs.reserve(nodes.size());
  for (const auto& n : nodes) {
    node_defs.push_back(&n);
  }
  return GraphConstructor::Construct(opts, node_defs, nullptr, nullptr, g,
                                     &refiner, nullptr,
                                     nullptr,
                                     nullptr);
}
