TypedValue HHVM_FUNCTION(array_intersect_assoc,
                         const Variant& array1,
                         const Variant& array2,
                         const Array& args ) {
  diff_intersect_body(intersect, args, true COMMA true);
}
