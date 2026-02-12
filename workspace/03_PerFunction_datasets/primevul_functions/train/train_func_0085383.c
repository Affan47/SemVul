bool HHVM_FUNCTION(krsort,
                   VRefParam array,
                   int sort_flags ) {
  bool use_zend_sort = RuntimeOption::EnableZendSorting;
  return php_ksort(array, sort_flags, false, use_zend_sort);
}
