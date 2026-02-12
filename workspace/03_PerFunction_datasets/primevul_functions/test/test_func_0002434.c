Status MaxPoolShape(shape_inference::InferenceContext* c) {
  return MaxPoolShapeImpl(c, false);
}
