string_open_failed(int eno, const char *format, ...)
{
va_list ap;
gstring * g = string_get(1024);

g = string_catn(g, US"failed to open ", 15);


va_start(ap, format);
(void) string_vformat(g, FALSE, format, ap);
string_from_gstring(g);
gstring_reset_unused(g);
va_end(ap);

return eno == EACCES
  ? string_sprintf("%s: %s (euid=%ld egid=%ld)", g->s, strerror(eno),
    (long int)geteuid(), (long int)getegid())
  : string_sprintf("%s: %s", g->s, strerror(eno));
}
