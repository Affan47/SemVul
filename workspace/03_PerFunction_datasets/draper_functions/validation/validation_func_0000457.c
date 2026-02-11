es3_printer_init_func(stp_vars_t *v)
{
  char pg = (strcmp(privdata.pagesize, "Postcard") == 0 ? 0x1:
	     (strcmp(privdata.pagesize, "w253h337") == 0 ? 0x2 :
	      (strcmp(privdata.pagesize, "w155h244") == 0 ? 0x3 : 0x1)));


  stp_put16_be(0x4000, v);
  stp_putc(pg, v);
  stp_putc(0x0, v);
  dyesub_nputc(v, 0x0, 8);
  stp_put32_le(privdata.w_size * privdata.h_size, v);
}
