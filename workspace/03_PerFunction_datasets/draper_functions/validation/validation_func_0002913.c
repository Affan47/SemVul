linputsoc_t(T_SOC soc, char *s, int max, int timeout) {
  if (check_readinput_t(soc, timeout)) {
    return linputsoc(soc, s, max);
  }
  return -1;
}
