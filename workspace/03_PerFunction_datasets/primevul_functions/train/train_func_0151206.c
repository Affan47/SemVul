void HeaderMapImpl::addCopy(const LowerCaseString& key, uint64_t value) {


  HeaderString new_key;
  new_key.setCopy(key.get());
  HeaderString new_value;
  new_value.setInteger(value);
  insertByKey(std::move(new_key), std::move(new_value));
  ASSERT(new_key.empty());
  ASSERT(new_value.empty());
}
