void unicode_error_callback(const void* context, UConverterToUnicodeArgs* args,
                            const char* codeUnits, int32_t length,
                            UConverterCallbackReason reason,
                            UErrorCode* pErrorCode) {


  bool* format_error = const_cast<bool*>(static_cast<const bool*>(context));

  if (reason == UCNV_UNASSIGNED || reason == UCNV_ILLEGAL ||
      reason == UCNV_IRREGULAR) {
    *format_error = true;
  }


  UCNV_TO_U_CALLBACK_SUBSTITUTE(nullptr, args, codeUnits, length, reason,
                                pErrorCode);
}
