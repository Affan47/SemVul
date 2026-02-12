int64_t HHVM_FUNCTION(intval, const Variant& v, int64_t base ) {
  return v.toInt64(base);
}
