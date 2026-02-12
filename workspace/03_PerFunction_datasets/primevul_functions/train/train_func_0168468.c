find_boundary (struct MHD_PostProcessor *pp,
               const char *boundary,
               size_t blen,
               size_t *ioffptr,
               enum PP_State next_state,
               enum PP_State next_dash_state)
{
  char *buf = (char *) &pp[1];
  const char *dash;

  if (pp->buffer_pos < 2 + blen)
  {
    if (pp->buffer_pos == pp->buffer_size)
      pp->state = PP_Error;

    return MHD_NO;
  }
  if ( (0 != memcmp ("--",
                     buf,
                     2)) ||
       (0 != memcmp (&buf[2],
                     boundary,
                     blen)))
  {
    if (pp->state != PP_Init)
    {

      pp->state = PP_Error;
    }
    else
    {

      dash = memchr (buf,
                     '-',
                     pp->buffer_pos);
      if (NULL == dash)
        (*ioffptr) += pp->buffer_pos;
      else if (dash == buf)
        (*ioffptr)++;
      else
        (*ioffptr) += dash - buf;
    }
    return MHD_NO;
  }

  (*ioffptr) += 2 + blen;

  pp->skip_rn = RN_Dash;
  pp->state = next_state;
  pp->dash_state = next_dash_state;
  return MHD_YES;
}
