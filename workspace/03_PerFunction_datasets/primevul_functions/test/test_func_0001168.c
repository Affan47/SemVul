Status ConstantFolding::RemoveShuffleOrTranspose(
    const GraphProperties& properties, bool use_shape_info,
    GraphDef* optimized_graph, NodeDef* node) {
  if (!use_shape_info || !(IsShuffle(*node) || IsTranspose(*node)))
    return Status::OK();
  Tensor permutation_tensor;
  if (GetTensorFromConstNode(node->input(1), &permutation_tensor) &&
      properties.HasInputProperties(node->name())) {
    const auto& shape = properties.GetInputProperties(node->name())[0].shape();
    std::vector<int> permutation;
    for (int j = 0; j < permutation_tensor.NumElements(); ++j) {
      if (permutation_tensor.dtype() == DT_INT64) {
        permutation.push_back(permutation_tensor.vec<int64_t>()(j));
      } else {
        permutation.push_back(permutation_tensor.vec<int>()(j));
      }
    }
    int permutation_size = permutation.size();
    if (permutation_size != shape.dim_size()) {

      return Status::OK();
    }


    bool replaceable = true;
    for (int j = 0; replaceable && j < shape.dim_size(); ++j) {
      replaceable &= shape.dim(j).size() == 1 || j == permutation[j];
    }
    if (replaceable) {
      ReplaceOperationWithIdentity(0, properties, node, optimized_graph);
    }
  }
  return Status::OK();
}
