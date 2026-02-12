int64_t TensorByteSize(const TensorProto& t) {

  int64_t num_elems = TensorShape(t.tensor_shape()).num_elements();
  return num_elems < 0 ? -1 : num_elems * DataTypeSize(t.dtype());
}
