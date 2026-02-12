Status DenseCountSparseOutputShapeFn(InferenceContext *c) {
  auto values = c->input(0);
  auto weights = c->input(1);
  ShapeHandle output;
  auto num_weights = c->NumElements(weights);
  if (c->ValueKnown(num_weights) && c->Value(num_weights) == 0) {
    output = values;
  } else {
    TF_RETURN_IF_ERROR(c->Merge(weights, values, &output));
  }
  auto rank = c->Rank(output);
  auto nvals = c->UnknownDim();
  c->set_output(0, c->Matrix(nvals, rank));
  c->set_output(1, c->Vector(nvals));
  c->set_output(2, c->Vector(rank));
  return Status::OK();
}
