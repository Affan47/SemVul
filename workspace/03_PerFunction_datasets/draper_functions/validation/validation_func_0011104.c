pf_output_text (const sc_char *string)
{
  sc_int index_, b_index;
  sc_char *buffer;


  if (!(strstr (string, ENTITY_LESSTHAN)
        || strstr (string, ENTITY_GREATERTHAN)
        || strstr (string, ENTITY_PERCENT)))
    {
      if_print_string (string);
      return;
    }


  buffer = sc_malloc (strlen (string) + 1);
  for (index_ = 0, b_index = 0;
       string[index_] != NUL; index_++, b_index++)
    {
      if (sc_strncasecmp (string + index_,
                          ENTITY_LESSTHAN, ENTITY_LENGTH) == 0)
        {
          buffer[b_index] = LESSTHAN;
          index_ += ENTITY_LENGTH - 1;
        }
      else if (sc_strncasecmp (string + index_,
                               ENTITY_GREATERTHAN, ENTITY_LENGTH) == 0)
        {
          buffer[b_index] = GREATERTHAN;
          index_ += ENTITY_LENGTH - 1;
        }
      else if (sc_strncasecmp (string + index_,
                               ENTITY_PERCENT, PERCENT_LENGTH) == 0)
        {
          buffer[b_index] = PERCENT;
          index_ += PERCENT_LENGTH - 1;
        }
      else
        buffer[b_index] = string[index_];
    }


  buffer[b_index] = NUL;
  if_print_string (buffer);
  sc_free (buffer);
}
