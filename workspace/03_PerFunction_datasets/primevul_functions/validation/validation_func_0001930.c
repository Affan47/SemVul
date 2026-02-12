void MoveAttrValue(std::vector<string>&& value, AttrValue* out) {
  out->mutable_list()->Clear();
  for (auto& v : value) {
    out->mutable_list()->add_s(std::move(v));
  }
}
