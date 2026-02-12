Status ConcatV2Shape(InferenceContext* c) {
  return ConcatShapeHelper(c, 0 ,
                           c->num_inputs() - 1 ,
                           c->num_inputs() - 1 );
}
