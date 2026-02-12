post_process_urlencoded (struct MHD_PostProcessor *pp,
                         const char *post_data,
                         size_t post_data_len)
{
  char *kbuf = (char *) &pp[1];
  size_t poff;
  const char *start_key = NULL;
  const char *end_key = NULL;
  const char *start_value = NULL;
  const char *end_value = NULL;
  const char *last_escape = NULL;

  poff = 0;
  while ( ( (poff < post_data_len) ||
            (pp->state == PP_Callback) ) &&
          (pp->state != PP_Error) )
  {
    switch (pp->state)
    {
    case PP_Error:

      abort ();
      break;
    case PP_Init:

      if (NULL == start_key)
        start_key = &post_data[poff];
      pp->must_ikvi = true;
      switch (post_data[poff])
      {
      case '=':

        end_key = &post_data[poff];
        poff++;
        pp->state = PP_ProcessValue;
        break;
      case '&':

        end_key = &post_data[poff];
        mhd_assert (NULL == start_value);
        mhd_assert (NULL == end_value);
        poff++;
        pp->state = PP_Callback;
        break;
      case '\n':
      case '\r':

        end_key = &post_data[poff];
        poff++;
        pp->state = PP_Done;
        break;
      default:

        poff++;
        continue;
      }
      break;
    case PP_ProcessValue:
      if (NULL == start_value)
        start_value = &post_data[poff];
      switch (post_data[poff])
      {
      case '=':

        pp->state = PP_Error;
        continue;
      case '&':

        end_value = &post_data[poff];
        poff++;
        if (pp->must_ikvi ||
            (start_value != end_value) )
        {
          pp->state = PP_Callback;
        }
        else
        {
          pp->buffer_pos = 0;
          pp->value_offset = 0;
          pp->state = PP_Init;
          start_value = NULL;
        }
        continue;
      case '\n':
      case '\r':

        end_value = &post_data[poff];
        poff++;
        if (pp->must_ikvi)
          pp->state = PP_Callback;
        else
          pp->state = PP_Done;
        break;
      case '%':
        last_escape = &post_data[poff];
        poff++;
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':

        poff++;
        continue;
      default:

        last_escape = NULL;
        poff++;
        continue;
      }
      break;
    case PP_Done:
      switch (post_data[poff])
      {
      case '\n':
      case '\r':
        poff++;
        continue;
      }

      pp->state = PP_Error;
      break;
    case PP_Callback:
      if ( (pp->buffer_pos + (end_key - start_key) >=
            pp->buffer_size) ||
           (pp->buffer_pos + (end_key - start_key) <
            pp->buffer_pos) )
      {

        pp->state = PP_Error;
        continue;
      }

      if (NULL != start_key)
      {
        memcpy (&kbuf[pp->buffer_pos],
                start_key,
                end_key - start_key);
        pp->buffer_pos += end_key - start_key;
        start_key = NULL;
        end_key = NULL;
        pp->must_unescape_key = true;
      }
      if (pp->must_unescape_key)
      {
        kbuf[pp->buffer_pos] = '\0';
        MHD_unescape_plus (kbuf);
        MHD_http_unescape (kbuf);
        pp->must_unescape_key = false;
      }
      process_value (pp,
                     start_value,
                     end_value,
                     NULL);
      pp->value_offset = 0;
      start_value = NULL;
      end_value = NULL;
      pp->buffer_pos = 0;
      pp->state = PP_Init;
      break;
    default:
      mhd_panic (mhd_panic_cls,
                 __FILE__,
                 __LINE__,
                 NULL);
    }
  }


  if (NULL != start_key)
  {
    if (NULL == end_key)
      end_key = &post_data[poff];
    if (pp->buffer_pos + (end_key - start_key) >= pp->buffer_size)
    {
      pp->state = PP_Error;
      return MHD_NO;
    }
    memcpy (&kbuf[pp->buffer_pos],
            start_key,
            end_key - start_key);
    pp->buffer_pos += end_key - start_key;
    pp->must_unescape_key = true;
    start_key = NULL;
    end_key = NULL;
  }
  if ( (NULL != start_value) &&
       (PP_ProcessValue == pp->state) )
  {

    if (pp->must_unescape_key)
    {
      kbuf[pp->buffer_pos] = '\0';
      MHD_unescape_plus (kbuf);
      MHD_http_unescape (kbuf);
      pp->must_unescape_key = false;
    }
    if (NULL == end_value)
      end_value = &post_data[poff];
    process_value (pp,
                   start_value,
                   end_value,
                   last_escape);
    pp->must_ikvi = false;
  }
  if (PP_Error == pp->state)
  {

    return MHD_NO;
  }
  return MHD_YES;
}
