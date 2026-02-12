void ConstantFolding::SimplifySqueeze(const GraphProperties& properties,
                                      bool use_shape_info,
                                      GraphDef* optimized_graph,
                                      NodeDef* node) {
  if (use_shape_info && IsSqueeze(*node) &&
      !properties.GetInputProperties(node->name()).empty()) {


    const auto& shape = properties.GetInputProperties(node->name())[0].shape();


    bool replaceable = !shape.unknown_rank();
    for (int j = 0; replaceable && j < shape.dim_size(); ++j) {
      replaceable &= shape.dim(j).size() > 1;
    }
    if (replaceable) {
      ReplaceOperationWithIdentity(0, properties, node, optimized_graph);
    }
  }
}
