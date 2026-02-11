mem_read_a000_bfff_default(Uint16 adr) {
  if (!ram_enable) return 0xff;
  return ram_page[active_ram_page][adr-0xa000];
}
