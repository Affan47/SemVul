describe_vote(struct vote *pvote, char *buf, int buflen)
{
  int ret = 0;


  if (pvote->flags & VCF_NODISSENT) {
    ret = fc_snprintf(buf, buflen,


        _("%s (needs %0.0f%% and no dissent)."),
        pvote->cmdline, MIN(100.0, pvote->need_pc * 100.0 + 1));
  } else {
    ret = fc_snprintf(buf, buflen,


        _("%s (needs %0.0f%% in favor)."),
        pvote->cmdline, MIN(100.0, pvote->need_pc * 100.0 + 1));
  }

  return ret;
}
