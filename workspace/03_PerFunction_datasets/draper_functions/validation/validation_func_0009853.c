do_cmd_push_key(struct anthy_input_context* ictx, const char* str)
{
  const char* p;

  for (p = str; *p; p++) {
    if (isspace((int)(unsigned char) *p) && *p != ' ')
      continue;

    rk_push_key(ictx->rkctx, *p);
    read_rk_result(ictx);
  }
}
