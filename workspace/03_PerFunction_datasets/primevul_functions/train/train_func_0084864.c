Status InferenceContext::MakeShapeFromTensor(const Tensor* t,
                                             ShapeHandle tensor_shape,
                                             ShapeHandle* out) {
  return InternalMakeShapeFromTensor(
      false , t, tensor_shape,
      out);
}
