do_execute (char const *buf, size_t size, size_t *match_size, char const *start_ptr)
{
  size_t result;
  const char *line_next;


  if (MB_CUR_MAX == 1 || !match_icase)
    return execute (buf, size, match_size, start_ptr);

  for (line_next = buf; line_next < buf + size; )
    {
      const char *line_buf = line_next;
      const char *line_end = memchr (line_buf, eolbyte, (buf + size) - line_buf);
      if (line_end == NULL)
        line_next = line_end = buf + size;
      else
        line_next = line_end + 1;

      if (start_ptr && start_ptr >= line_end)
        continue;

      result = execute (line_buf, line_next - line_buf, match_size, start_ptr);
      if (result != (size_t) -1)
        return (line_buf - buf) + result;
    }

  return (size_t) -1;
}
