void HeaderMapImpl::appendCopy(const LowerCaseString& key, absl::string_view value) {

  auto entry = getExisting(key);
  if (!entry.empty()) {
    const uint64_t added_size = appendToHeader(entry[0]->value(), value);
    addSize(added_size);
  } else {
    addCopy(key, value);
  }
}
