Status QuantizedConcatV2Shape(InferenceContext* c, int num_inputs_to_concat) {
  return ConcatShapeHelper(c, 0 ,
                           num_inputs_to_concat ,
                           num_inputs_to_concat );
}
