log_set_snomask(const char *subsys, const char *snomask)
{
  struct LogDesc *desc;
  unsigned int sno = SNO_DEFAULT;


  if (!(desc = log_find(subsys)))
    return 2;


  if (EmptyString(snomask)) {
    desc->snomask = desc->def_sno;
    desc->mark &= ~LOG_MARK_SNOMASK;
  } else if ((sno = log_sno_find(snomask)) != SNO_NOTFOUND) {
    desc->snomask = sno;
    if (sno == desc->def_sno)
      desc->mark &= ~LOG_MARK_SNOMASK;
    else
      desc->mark |= LOG_MARK_SNOMASK;
  } else
    return 1;

  return 0;
}
