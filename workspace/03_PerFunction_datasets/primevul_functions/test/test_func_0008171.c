bool ReadPartialShapesFromShapeMap(
    const Node* n,
    const std::unordered_map<string, std::vector<PartialTensorShape>>*
        shape_map,
    std::vector<PartialTensorShape>* input_shapes) {
  CHECK(shape_map != nullptr);
  input_shapes->resize(n->num_inputs());
  for (const Edge* in : n->in_edges()) {

    if (in->IsControlEdge()) continue;
    const auto known_shape_iter = shape_map->find(in->src()->name());
    if (known_shape_iter == shape_map->end()) {

      return false;
    }
    const auto& known_shape = known_shape_iter->second;
    CHECK_GT(known_shape.size(), in->src_output()) << known_shape_iter->first;
    DCHECK_GE(in->dst_input(), 0);
    DCHECK_LT(in->dst_input(), input_shapes->size());
    (*input_shapes)[in->dst_input()] = known_shape[in->src_output()];
  }
  return true;
}
