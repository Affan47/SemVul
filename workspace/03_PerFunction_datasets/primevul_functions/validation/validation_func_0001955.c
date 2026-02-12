void SetAttrValue(gtl::ArraySlice<NameAttrList> value, AttrValue* out) {
  out->mutable_list()->Clear();
  for (const auto& v : value) {
    *out->mutable_list()->add_func() = v;
  }
}
