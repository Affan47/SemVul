convert_charset( char *input )
{
#ifdef HAVE_ICONV
  const int expansion_factor = 3;
  static char *output = NULL;
  static size_t output_size = 0;
  char* output_ptr = output;
  size_t output_left = output_size;
  ICONV_CONST char* input_ptr = input;
  size_t input_left = strlen( input ) + 1;
  size_t min_output_size = input_left * expansion_factor;

  if( conversion_descriptor == (iconv_t)(-1) ) return input;

  if( output_size == 0 || output_size < min_output_size ) {
    output = realloc( output, min_output_size );
    if( output == NULL ) {
      output_size = 0;
      return input;
    }
    output_ptr = output;
    output_size = input_left * expansion_factor;
    output_left = output_size;
    *output = '\0';
  }

  if( (size_t)(-1) == iconv( conversion_descriptor, &input_ptr, &input_left,
                             &output_ptr, &output_left ) ) {
    return input;
  }


  if( (size_t)(-1) == iconv( conversion_descriptor, NULL, NULL, &output_ptr,
                             &output_left ) ) {
    return input;
  }

  return output;
#else
  return input;
#endif
}
