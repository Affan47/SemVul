TypedValue HHVM_FUNCTION(array_change_key_case,
                         ArrayArg input,
                         int64_t case_ ) {
  return tvReturn(ArrayUtil::ChangeKeyCase(ArrNR(input.get()),
                                           (CaseMode)case_ == CaseMode::LOWER));
}
