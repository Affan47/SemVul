caml_format_int(value fmt, value arg)
{
  char format_string[FORMAT_BUFFER_SIZE];
  char default_format_buffer[FORMAT_BUFFER_SIZE];
  char * buffer;
  char conv;
  value res;

  buffer = parse_format(fmt, ARCH_INTNAT_PRINTF_FORMAT,
                       format_string, default_format_buffer, &conv);
  switch (conv) {
  case 'u': case 'x': case 'X': case 'o':
    sprintf(buffer, format_string, Unsigned_long_val(arg));
    break;
  default:
    sprintf(buffer, format_string, Long_val(arg));
    break;
  }
  res = caml_copy_string(buffer);
  if (buffer != default_format_buffer) caml_stat_free(buffer);
  return res;
}
