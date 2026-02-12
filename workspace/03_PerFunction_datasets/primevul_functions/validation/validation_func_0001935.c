bool AreTensorProtosEqual(const TensorProto& lhs, const TensorProto& rhs,
                          bool allow_false_negatives) {


  const int64_t lhs_tensor_bytes = TensorByteSize(lhs);
  const int64_t rhs_tensor_bytes = TensorByteSize(rhs);
  if (lhs_tensor_bytes != rhs_tensor_bytes) {
    return false;
  }


  const int64_t lhs_proto_bytes = lhs.ByteSizeLong();
  const bool large_expansion =
      (lhs_proto_bytes < 512 && lhs_tensor_bytes > 4096);


  const bool only_compare_proto =
      (allow_false_negatives && lhs_tensor_bytes > kMaxAttrValueTensorByteSize);
  if (large_expansion || only_compare_proto) {
    if (AreSerializedProtosEqual(lhs, rhs))
      return true;
    else if (only_compare_proto)
      return false;
  }


  Tensor lhs_t(lhs.dtype());
  bool success = lhs_t.FromProto(lhs);
  if (!success) {
    return false;
  }

  Tensor rhs_t(rhs.dtype());
  success = rhs_t.FromProto(rhs);
  if (!success) {
    return false;
  }

  TensorProto lhs_tp;
  lhs_t.AsProtoTensorContent(&lhs_tp);

  TensorProto rhs_tp;
  rhs_t.AsProtoTensorContent(&rhs_tp);

  return AreSerializedProtosEqual(lhs_tp, rhs_tp);
}
