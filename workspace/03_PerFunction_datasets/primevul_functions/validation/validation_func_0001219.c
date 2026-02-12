bool HHVM_FUNCTION(HH_is_php_array, const Variant& v) {


  return is_php_array(v.asTypedValue());
}
