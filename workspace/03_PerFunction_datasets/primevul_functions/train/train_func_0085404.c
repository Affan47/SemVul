TypedValue HHVM_FUNCTION(array_diff_assoc,
                         const Variant& array1,
                         const Variant& array2,
                         const Array& args ) {
  diff_intersect_body(diff, args, true COMMA true);
}
