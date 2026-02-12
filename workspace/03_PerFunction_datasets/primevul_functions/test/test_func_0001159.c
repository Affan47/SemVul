bool ConstantFolding::IsFoldableUncached(
    const NodeDef& node, const GraphProperties* properties) const {

  if (node.input().empty()) {
    return false;
  }


  bool merge_has_constant_input = false;
  const bool is_merge = IsMerge(node);
  for (const auto& input : node.input()) {
    if (IsControlInput(input)) {
      continue;
    }
    const NodeDef* input_node = node_map_->GetNode(input);
    if (!input_node) {
      return false;
    }
    bool is_const = IsReallyConstant(*input_node);
    if (is_const) {


      if (input_node->attr().count("dtype") == 0 ||
          input_node->attr().at("dtype").type() == DT_STRING) {
        return false;
      }


      merge_has_constant_input |= !HasControlInputs(*input_node);
    } else if (!is_merge) {
      return false;
    }
  }
  if (is_merge && !merge_has_constant_input) return false;
  if (disable_compressed_tensor_optimization_ &&
      (IsFill(node) || IsZerosLike(node) || IsOnesLike(node)))
    return false;


  if (properties != nullptr && properties->HasOutputProperties(node.name())) {
    const std::vector<OpInfo::TensorProperties>& input_props =
        properties->GetInputProperties(node.name());
    const std::vector<OpInfo::TensorProperties>& output_props =
        properties->GetOutputProperties(node.name());

    int64_t input_size_bytes = 0;
    for (const auto& input_prop : input_props) {
      const PartialTensorShape input_shape(input_prop.shape());
      if (input_shape.IsFullyDefined()) {
        input_size_bytes +=
            input_shape.num_elements() * DataTypeSize(input_prop.dtype());
      }
    }
    for (const auto& output_prop : output_props) {
      const PartialTensorShape output_shape(output_prop.shape());
      if (output_shape.IsFullyDefined()) {
        const int64_t num_bytes =
            output_shape.num_elements() * DataTypeSize(output_prop.dtype());
        if (num_bytes > input_size_bytes && num_bytes > kMaxConstantSize) {


          return false;
        }
      }
    }
  }

  return true;
}
