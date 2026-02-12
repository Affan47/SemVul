void HeaderMapImpl::addCopy(const LowerCaseString& key, absl::string_view value) {


  HeaderString new_key;
  new_key.setCopy(key.get());
  HeaderString new_value;
  new_value.setCopy(value);
  insertByKey(std::move(new_key), std::move(new_value));
  ASSERT(new_key.empty());
  ASSERT(new_value.empty());
}
