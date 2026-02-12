void ConsiderConstantFoldableNode(
    Node* n, const ConstantFoldingOptions& opts, std::vector<Node*>* nodes,
    std::unordered_map<const Node*, gtl::FlatSet<Node*>>* constant_control_deps,
    std::unordered_map<const Node*, std::vector<Tensor>>* shape_replacement_map,
    bool* internal_node_inserted) {
  if (IsConstantFoldable(n, opts.shape_map, opts.consider,
                         opts.max_constant_size_in_bytes,
                         shape_replacement_map)) {


    bool all_parents_constant = true;
    for (const Edge* in : n->in_edges()) {

      if (!in->IsControlEdge() &&
          constant_control_deps->count(in->src()) == 0) {
        all_parents_constant = false;
        break;
      }
    }
    if (all_parents_constant || shape_replacement_map->count(n) != 0) {
      gtl::FlatSet<Node*>& control_deps = (*constant_control_deps)[n];
      for (const Edge* e : n->in_edges()) {
        if (constant_control_deps->count(e->src()) == 0) {


          if (!e->src()->IsSource()) {
            control_deps.insert(e->src());
          }
        } else {


          const gtl::FlatSet<Node*>& parent_deps =
              (*constant_control_deps)[e->src()];
          control_deps.insert(parent_deps.begin(), parent_deps.end());
        }
      }
      nodes->push_back(n);
      if (!n->IsConstant()) {
        *internal_node_inserted = true;
      }
    }
  }
}
