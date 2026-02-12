process_value_to_boundary (struct MHD_PostProcessor *pp,
                           size_t *ioffptr,
                           const char *boundary,
                           size_t blen,
                           enum PP_State next_state,
                           enum PP_State next_dash_state)
{
  char *buf = (char *) &pp[1];
  size_t newline;
  const char *r;


  newline = 0;
  while (1)
  {
    while (newline + 4 < pp->buffer_pos)
    {
      r = memchr (&buf[newline],
                  '\r',
                  pp->buffer_pos - newline - 4);
      if (NULL == r)
      {
        newline = pp->buffer_pos - 4;
        break;
      }
      newline = r - buf;
      if (0 == memcmp ("\r\n--",
                       &buf[newline],
                       4))
        break;
      newline++;
    }
    if (newline + blen + 4 <= pp->buffer_pos)
    {

      if (0 != memcmp (&buf[newline + 4],
                       boundary,
                       blen))
      {

        newline += 4;
        continue;
      }
      else
      {


        pp->skip_rn = RN_Dash;
        pp->state = next_state;
        pp->dash_state = next_dash_state;
        (*ioffptr) += blen + 4;
        buf[newline] = '\0';
        break;
      }
    }
    else
    {


      if ( (0 == newline) &&
           (pp->buffer_pos == pp->buffer_size) )
      {
        pp->state = PP_Error;
        return MHD_NO;
      }
      break;
    }
  }


  if ( ( (pp->must_ikvi) ||
         (0 != newline) ) &&
       (MHD_NO == pp->ikvi (pp->cls,
                            MHD_POSTDATA_KIND,
                            pp->content_name,
                            pp->content_filename,
                            pp->content_type,
                            pp->content_transfer_encoding,
                            buf,
                            pp->value_offset,
                            newline)) )
  {
    pp->state = PP_Error;
    return MHD_NO;
  }
  pp->must_ikvi = false;
  pp->value_offset += newline;
  (*ioffptr) += newline;
  return MHD_YES;
}
