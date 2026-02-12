String HHVM_FUNCTION(gettype, const Variant& v) {
  if (v.getType() == KindOfResource && v.toCResRef().isInvalid()) {
    return s_unknown_type;
  }


  if (v.isNull()) {
    return s_NULL;
  }


  if (isArrayType(v.getType())) {
    maybe_raise_array_serialization_notice(SerializationSite::Gettype,
                                           v.getArrayData());
    return s_array;
  }
  if (isArrayLikeType(v.getType()) && v.getArrayData()->isLegacyArray()) {
    return s_array;
  }
  if (RuntimeOption::EvalClassAsStringGetType &&
      (v.isLazyClass() || v.isClass())) {
    return s_string;
  }
  return getDataTypeString(v.getType());
}
