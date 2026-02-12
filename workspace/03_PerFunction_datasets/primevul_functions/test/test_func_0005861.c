Status RaggedCountSparseOutputShapeFn(InferenceContext *c) {
  int32_t rank = c->Rank(c->input(1));
  if (rank != c->kUnknownRank) {
    ++rank;
  }
  auto nvals = c->UnknownDim();
  c->set_output(0, c->Matrix(nvals, rank));
  c->set_output(1, c->Vector(nvals));
  c->set_output(2, c->Vector(rank));
  return Status::OK();
}
