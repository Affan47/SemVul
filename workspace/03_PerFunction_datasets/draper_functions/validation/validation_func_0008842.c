sanei_pa4s2_enable (int fd, int enable)
{

  TEST_DBG_INIT ();

  DBG (4, "sanei_pa4s2_enable: called for fd %d with value=%d\n",
       fd, enable);
  DBG (2, "sanei_pa4s2_enable: fd %d is invalid\n", fd);

  if ((enable != SANE_TRUE) && (enable != SANE_FALSE))
    DBG (2, "sanei_pa4s2_enable: value %d is invalid\n", enable);

  DBG (3, "sanei_pa4s2_enable: A4S2 support not compiled\n");
  DBG (6, "sanei_pa4s2_enable: oops, I think there's someone going to\n");
  DBG (6, "sanei_pa4s2_enable: produce a lot of garbage...\n");
  DBG (5, "sanei_pa4s2_enable: returning SANE_STATUS_INVAL\n");

  return SANE_STATUS_INVAL;
}
