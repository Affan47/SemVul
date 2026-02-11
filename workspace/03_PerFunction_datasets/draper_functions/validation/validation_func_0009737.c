router_pick_published_address(const or_options_t *options, uint32_t *addr)
{
  if (resolve_my_address(LOG_INFO, options, addr, NULL) < 0) {
    log_info(LD_CONFIG, "Could not determine our address locally. "
             "Checking if directory headers provide any hints.");
    if (router_guess_address_from_dir_headers(addr) < 0) {
      log_info(LD_CONFIG, "No hints from directory headers either. "
               "Will try again later.");
      return -1;
    }
  }
  log_info(LD_CONFIG,"Success: chose address '%s'.", fmt_addr32(*addr));
  return 0;
}
