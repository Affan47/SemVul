print_dsn_diagnostic_code(const address_item *addr, FILE *f)
{
uschar *s = testflag(addr, af_pass_message) ? addr->message : NULL;


if (s)
  {
  DEBUG(D_deliver)
    debug_printf("DSN Diagnostic-Code: addr->message = %s\n", addr->message);


  if (!(s = Ustrstr(addr->message, ": ")))
    return;
  s += 2;
  fprintf(f, "Diagnostic-Code: smtp; ");
  }

else return;

while (*s)
  if (*s == '\\' && s[1] == 'n')
    {
    fputs("\n ", f);
    s += 2;
    }
  else
    fputc(*s++, f);

fputc('\n', f);
}
