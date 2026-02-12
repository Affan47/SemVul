PARAMETER *rfc2231_encode_string (const char *attribute, char *value)
{
  int encode = 0, add_quotes = 0, free_src_value = 0;
  int split = 0, continuation_number = 0;
  size_t dest_value_len = 0, max_value_len = 0, cur_value_len = 0;
  char *cur, *charset = NULL, *src_value = NULL;
  PARAMETER *result = NULL, *current, **lastp;
  BUFFER *cur_attribute, *cur_value;

  cur_attribute = mutt_buffer_pool_get ();
  cur_value = mutt_buffer_pool_get ();


  for (cur = value; *cur; cur++)
    if (*cur < 0x20 || *cur >= 0x7f)
    {
      encode = 1;
      break;
    }

  if (encode)
  {
    if (Charset && SendCharset)
      charset = mutt_choose_charset (Charset, SendCharset,
                                     value, mutt_strlen (value),
                                     &src_value, NULL);
    if (src_value)
      free_src_value = 1;
    if (!charset)
      charset = safe_strdup (Charset ? Charset : "unknown-8bit");
  }
  if (!src_value)
    src_value = value;


  if (encode)
    dest_value_len = mutt_strlen (charset) + 2;

  for (cur = src_value; *cur; cur++)
  {
    dest_value_len++;

    if (encode)
    {

      if (*cur < 0x20 || *cur >= 0x7f ||
          strchr (MimeSpecials, *cur) ||
          strchr ("*'%", *cur))
      {
        dest_value_len += 2;
      }
    }
    else
    {

      if (!add_quotes && strchr (MimeSpecials, *cur))
        add_quotes = 1;

      if (*cur == '\\' || *cur == '"')
        dest_value_len++;
    }
  }


  max_value_len =
    78                      -
    1                       -
    mutt_strlen (attribute) -
    (encode ? 1 : 0)        -
    1                       -
    (add_quotes ? 2 : 0)    -
    1;

  if (max_value_len < 30)
    max_value_len = 30;

  if (dest_value_len > max_value_len)
  {
    split = 1;
    max_value_len -= 4;

  }


  lastp = &result;
  cur = src_value;
  if (encode)
  {
    mutt_buffer_printf (cur_value, "%s''", charset);
    cur_value_len = mutt_buffer_len (cur_value);
  }

  while (*cur)
  {
    *lastp = current = mutt_new_parameter ();
    lastp = &current->next;
    mutt_buffer_strcpy (cur_attribute, attribute);
    if (split)
      mutt_buffer_add_printf (cur_attribute, "*%d", continuation_number++);
    if (encode)
      mutt_buffer_addch (cur_attribute, '*');

    while (*cur && (!split || cur_value_len < max_value_len))
    {
      if (encode)
      {
        if (*cur < 0x20 || *cur >= 0x7f ||
            strchr (MimeSpecials, *cur) ||
            strchr ("*'%", *cur))
        {
          mutt_buffer_add_printf (cur_value, "%%%02X", (unsigned char)*cur);
          cur_value_len += 3;
        }
        else
        {
          mutt_buffer_addch (cur_value, *cur);
          cur_value_len++;
        }
      }
      else
      {
        mutt_buffer_addch (cur_value, *cur);
        cur_value_len++;
        if (*cur == '\\' || *cur == '"')
          cur_value_len++;
      }

      cur++;
    }

    current->attribute = safe_strdup (mutt_b2s (cur_attribute));
    current->value = safe_strdup (mutt_b2s (cur_value));

    mutt_buffer_clear (cur_value);
    cur_value_len = 0;
  }

  mutt_buffer_pool_release (&cur_attribute);
  mutt_buffer_pool_release (&cur_value);

  FREE (&charset);
  if (free_src_value)
    FREE (&src_value);

  return result;
}
