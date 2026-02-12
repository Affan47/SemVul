template <class T> std::unique_ptr<T> createHeaderMap(const HeaderMap& rhs) {


  auto new_header_map = T::create();
  HeaderMapImpl::copyFrom(*new_header_map, rhs);
  return new_header_map;
}
