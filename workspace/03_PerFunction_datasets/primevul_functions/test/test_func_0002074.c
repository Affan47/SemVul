uint64 NumElementsFromTensorProto(const TensorProto& tensor_proto) {
  if (!tensor_proto.has_tensor_shape()) {
    return -1;
  }
  const auto& tensor_shape_proto = tensor_proto.tensor_shape();
  if (tensor_shape_proto.unknown_rank()) {
    return -1;
  }
  int64_t num_elements = 1;
  for (const auto& dim : tensor_shape_proto.dim()) {

    num_elements *= dim.size();
  }
  return num_elements;
}
