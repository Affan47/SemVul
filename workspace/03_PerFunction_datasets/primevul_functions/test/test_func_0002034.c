bool ShouldUpdateOutputShapesAndValues(NodeContext* c, int64_t max_size) {
    InferenceContext* ic = c->inference_context.get();


    if (!IsAllowListedOpTypeForEvaluateNode(c->op_data->op_def.name())) {
      return false;
    }


    for (const auto& input_type : c->input_types) {
      if (!IsNumericType(input_type)) {
        return false;
      }
    }


    for (const auto& output_type : c->output_types) {
      if (!IsNumericType(output_type)) {
        return false;
      }
    }


    for (int i = 0; i < ic->num_inputs(); i++) {
      const Tensor* tensor = ic->input_tensor(i);
      const ShapeHandle& input_shape_handle = ic->input(i);
      if (tensor != nullptr) {
        if (tensor->NumElements() > max_size) {
          return false;
        }
      } else if (ic->Value(ic->NumElements(input_shape_handle)) > max_size) {
        return false;
      }
    }


    for (int i = 0; i < ic->num_outputs(); i++) {
      const ShapeHandle& shape_handle = ic->output(i);
      if (!ic->FullyDefined(shape_handle) ||
          ic->Value(ic->NumElements(shape_handle)) > max_size) {
        return false;
      }
    }
    return true;
  }
