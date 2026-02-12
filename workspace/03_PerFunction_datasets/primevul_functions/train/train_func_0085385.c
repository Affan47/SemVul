TypedValue HHVM_FUNCTION(array_reverse,
                         ArrayArg input,
                         bool preserve_keys ) {

  ArrNR arrNR(input.get());
  const Array& arr = arrNR.asArray();
  return tvReturn(ArrayUtil::Reverse(arr, preserve_keys));
}
