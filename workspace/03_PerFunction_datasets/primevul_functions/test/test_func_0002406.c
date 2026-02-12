Status MaxPoolShapeWithExplicitPadding(shape_inference::InferenceContext* c) {
  return MaxPoolShapeImpl(c, true);
}
