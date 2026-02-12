void SetAttrValue(const gtl::ArraySlice<TensorProto> value, AttrValue* out) {
  out->mutable_list()->Clear();
  for (const auto& v : value) {
    *out->mutable_list()->add_tensor() = v;
  }
}
