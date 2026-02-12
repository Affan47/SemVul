Status ConstantFolding::SimplifyStridedSlice(const GraphProperties& properties,
                                             bool use_shape_info,
                                             GraphDef* optimized_graph,
                                             NodeDef* node) {
  if (use_shape_info && IsStridedSlice(*node) &&
      properties.GetInputProperties(node->name()).size() == 4) {
    TF_RETURN_IF_ERROR(
        CheckAttrsExist(*node, {"new_axis_mask", "shrink_axis_mask"}));
    if (node->attr().at("new_axis_mask").i() != 0 ||
        node->attr().at("shrink_axis_mask").i() != 0) {


      return Status::OK();
    }
    const auto& input = properties.GetInputProperties(node->name())[0];
    for (int j = 0; j < input.shape().dim_size(); ++j) {

      if (input.shape().dim(j).size() < 0) {
        return Status::OK();
      }
    }

    std::vector<Tensor> input_tensors(3);
    for (int i = 1; i < 4; ++i) {
      if (!GetTensorFromConstNode(node->input(i), &input_tensors[i - 1])) {
        return Status::OK();
      }
    }

    const Tensor& begin = input_tensors[0];
    const Tensor& end = input_tensors[1];
    const Tensor& strides = input_tensors[2];

    TF_RETURN_IF_ERROR(
        CheckAttrsExist(*node, {"begin_mask", "end_mask", "ellipsis_mask"}));
    int begin_mask = node->attr().at("begin_mask").i();
    int end_mask = node->attr().at("end_mask").i();
    std::set<int> expanded_ellipsis_indices;
    int ellipsis_index = -1;
    for (int j = 0; j < input.shape().dim_size(); ++j) {


      if (node->attr().at("ellipsis_mask").i() & 1 << j ||
          (ellipsis_index == -1 && j >= strides.NumElements())) {
        ellipsis_index = j;
      }


      if (ellipsis_index != -1 &&
          input.shape().dim_size() >
              strides.NumElements() + j - ellipsis_index) {
        expanded_ellipsis_indices.insert(j);
      }
    }


    bool replaceable = !input.shape().unknown_rank();
    for (int j = 0; replaceable && j < input.shape().dim_size(); ++j) {
      if (expanded_ellipsis_indices.find(j) !=
          expanded_ellipsis_indices.end()) {

        continue;
      }


      int i = j;
      int expanded_ellipsis_indices_size = expanded_ellipsis_indices.size();
      if (ellipsis_index != -1 &&
          j >= ellipsis_index + expanded_ellipsis_indices_size) {
        i = j - expanded_ellipsis_indices_size;
      }
      int b = begin.dtype() == DT_INT32 ? begin.vec<int>()(i)
                                        : begin.vec<int64_t>()(i);
      int e =
          end.dtype() == DT_INT32 ? end.vec<int>()(i) : end.vec<int64_t>()(i);
      int s = strides.dtype() == DT_INT32 ? strides.vec<int>()(i)
                                          : strides.vec<int64_t>()(i);
      replaceable &= (begin_mask & 1 << i || b == 0) &&
                     (end_mask & 1 << i || e == input.shape().dim(j).size()) &&
                     s == 1;
    }
    if (replaceable) {
      ReplaceOperationWithIdentity(0, properties, node, optimized_graph);
    }
  }
  return Status::OK();
}
