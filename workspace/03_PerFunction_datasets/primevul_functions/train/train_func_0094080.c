bool FastAreTensorProtosEqual(const TensorProto& lhs, const TensorProto& rhs) {


  const int64 lhs_tensor_bytes = TensorByteSize(lhs);
  const int64 rhs_tensor_bytes = TensorByteSize(rhs);
  if (lhs_tensor_bytes != rhs_tensor_bytes) {
    return false;
  }


  if (lhs_tensor_bytes > kMaxAttrValueTensorByteSize) {
    return AreSerializedProtosEqual(lhs, rhs);
  }


  const int64 lhs_proto_bytes = lhs.ByteSizeLong();
  const bool large_expansion =
      (lhs_proto_bytes < 512 && lhs_tensor_bytes > 4096);
  if (large_expansion && AreSerializedProtosEqual(lhs, rhs)) {
    return true;
  }


  return AreTensorProtosEqual(lhs, rhs);
}
