bool HHVM_FUNCTION(arsort,
                   VRefParam array,
                   int sort_flags ) {
  bool use_zend_sort = RuntimeOption::EnableZendSorting;
  return php_asort(array, sort_flags, false, use_zend_sort);
}
