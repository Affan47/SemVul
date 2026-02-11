get_res(anthy_context_t ac, char *res_buf, int conv)
{
  struct anthy_conv_stat acs;
  int i;

  anthy_get_stat(ac, &acs);
  res_buf[0] = 0;
  if (!conv) {
    strcat(res_buf, "|");
  }
  for (i = 0; i < acs.nr_segment; i++) {
    char buf[1024];
    if (conv) {
      anthy_get_segment(ac, i, 0, buf, 1024);
      strcat(res_buf, buf);
    } else {
      anthy_get_segment(ac, i, NTH_UNCONVERTED_CANDIDATE, buf, 1024);
      strcat(res_buf, buf);
      strcat(res_buf, "|");
    }
  }
}
