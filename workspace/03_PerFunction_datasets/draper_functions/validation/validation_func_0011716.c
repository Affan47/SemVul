rk_reduce(struct rk_conv_context* cc,
	  struct rk_slr_closure* cur_state, char* buf, int size)
{
  struct rk_rule* r;
  const char* p;
  char* q, * end;

  r = cur_state->r;
  if (r == NULL || size <= 0)
    return 0;

  if (r->rhs[0] == SPECIAL_CHAR) {
    if (r->rhs[1] == 'o')
      rk_select_registered_map(cc, cc->old_map_no);
    else {
      int mapn = r->rhs[1] - '0';
      rk_select_registered_map(cc, mapn);
    }
    return 0;
  }

  p = r->rhs;
  q = buf;
  end = buf + size - 1;
  while (*p && q < end)
    *q ++ = *p++;
  *q = '\0';

  return q - buf;
}
