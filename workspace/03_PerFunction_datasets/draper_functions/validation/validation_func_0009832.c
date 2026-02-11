get_41_protocol_string(char **buffer,
                             size_t *max_bytes_available,
                             size_t *string_length)
{
  char *str= (char *)memchr(*buffer, '\0', *max_bytes_available);

  if (str == NULL)
    return NULL;

  *string_length= (size_t)(str - *buffer);
  *max_bytes_available-= *string_length + 1;
  str= *buffer;
  *buffer += *string_length + 1;

  return str;
}
