lexer_check_numbers (parser_context_t *context_p,
                     const uint8_t **source_p,
                     const uint8_t *source_end_p,
                     const ecma_char_t digit_max,
                     const bool is_legacy)
{
#if !JERRY_ESNEXT
  JERRY_UNUSED (context_p);
  JERRY_UNUSED (is_legacy);
#endif
  while (true)
  {
    while (*source_p < source_end_p && *source_p[0] >= LIT_CHAR_0 && *source_p[0] <= digit_max)
    {
      *source_p += 1;
    }
#if JERRY_ESNEXT
    if (*source_p != source_end_p && *source_p[0] == LIT_CHAR_UNDERSCORE)
    {
      *source_p += 1;
      if (is_legacy || *source_p == source_end_p || *source_p[0] == LIT_CHAR_UNDERSCORE || *source_p[0] > digit_max
          || *source_p[0] < LIT_CHAR_0)
      {
        parser_raise_error (context_p, PARSER_ERR_INVALID_UNDERSCORE_IN_NUMBER);
      }
      continue;
    }
#endif

    break;
  }
}
