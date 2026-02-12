String HHVM_FUNCTION(mb_output_handler,
                     const String& contents,
                     int status) {
  mbfl_string string, result;
  int last_feed;

  mbfl_encoding *encoding = MBSTRG(current_http_output_encoding);


  if (status & k_PHP_OUTPUT_HANDLER_START) {

    if (MBSTRG(outconv)) {
      MBSTRG(illegalchars) += mbfl_buffer_illegalchars(MBSTRG(outconv));
      mbfl_buffer_converter_delete(MBSTRG(outconv));
      MBSTRG(outconv) = nullptr;
    }
    if (encoding == nullptr) {
      return contents;
    }


    String mimetype = g_context->getMimeType();
    if (!mimetype.empty()) {
      const char *charset = encoding->mime_name;
      if (charset) {
        g_context->setContentType(mimetype, charset);
      }

      MBSTRG(outconv) = mbfl_buffer_converter_new2
        (MBSTRG(current_internal_encoding), encoding, 0);
    }
  }


  if (MBSTRG(outconv) == nullptr) {
    return contents;
  }


  last_feed = ((status & k_PHP_OUTPUT_HANDLER_END) != 0);

  mbfl_buffer_converter_illegal_mode
    (MBSTRG(outconv), MBSTRG(current_filter_illegal_mode));
  mbfl_buffer_converter_illegal_substchar
    (MBSTRG(outconv), MBSTRG(current_filter_illegal_substchar));


  mbfl_string_init(&string);
  string.no_language = MBSTRG(current_language);
  string.no_encoding = MBSTRG(current_internal_encoding)->no_encoding;
  string.val = (unsigned char *)contents.data();
  string.len = contents.size();
  mbfl_buffer_converter_feed(MBSTRG(outconv), &string);
  if (last_feed) {
    mbfl_buffer_converter_flush(MBSTRG(outconv));
  }

  mbfl_buffer_converter_result(MBSTRG(outconv), &result);


  if (last_feed) {
    MBSTRG(illegalchars) += mbfl_buffer_illegalchars(MBSTRG(outconv));
    mbfl_buffer_converter_delete(MBSTRG(outconv));
    MBSTRG(outconv) = nullptr;
  }

  return String(reinterpret_cast<char*>(result.val), result.len, AttachString);
}
