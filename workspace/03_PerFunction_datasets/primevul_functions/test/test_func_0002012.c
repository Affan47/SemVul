bool AllInputValuesKnown(NodeContext* c) {
    InferenceContext* ic = c->inference_context.get();


    for (int i = 0; i < ic->num_inputs(); i++) {
      const Tensor* tensor = ic->input_tensor(i);


      const ShapeHandle& input_tensors_as_shape =
          ic->input_tensors_as_shapes()[i];


      if (tensor == nullptr && !ic->FullyDefined(input_tensors_as_shape)) {
        return false;
      }
    }
    return true;
  }
