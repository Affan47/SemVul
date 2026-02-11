extensible_string_setup
   ___P((extensible_string *str,
         int n),
        (str,
         n)
extensible_string *str;
int n;)
{
#define EXTENSIBLE_STRING_INITIAL_BUFFER_SIZE 32

  if (n < EXTENSIBLE_STRING_INITIAL_BUFFER_SIZE)
    n = EXTENSIBLE_STRING_INITIAL_BUFFER_SIZE;

  str->buffer = ___CAST(extensible_string_char*,
                        ___alloc_mem (n * sizeof (extensible_string_char)));

  if (str->buffer == NULL)
    return ___FIX(___HEAP_OVERFLOW_ERR);

  str->length = 0;
  str->max_length = n;

  return ___FIX(___NO_ERR);
}
