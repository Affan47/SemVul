void SetAttrValue(gtl::ArraySlice<TensorShapeProto> value, AttrValue* out) {
  out->mutable_list()->Clear();
  for (const auto& v : value) {
    *out->mutable_list()->add_shape() = v;
  }
}
