Status ConcatShape(InferenceContext* c, int num_inputs_to_concat) {
  return ConcatShapeHelper(c, 1 ,
                           1 + num_inputs_to_concat ,
                           0 );
}
