use_printer_weave(const stp_vars_t *v)
{
  const res_t *res = stp_escp2_find_resolution(v);
  return (!res || res->command);
}
