string_open_failed(int eno, char *format, ...)
{
va_list ap;
uschar buffer[1024];

Ustrcpy(buffer, "failed to open ");
va_start(ap, format);


(void)string_vformat(buffer+15, sizeof(buffer) - 15, format, ap);

return (eno == EACCES)?
  string_sprintf("%s: %s (euid=%ld egid=%ld)", buffer, strerror(eno),
    (long int)geteuid(), (long int)getegid()) :
  string_sprintf("%s: %s", buffer, strerror(eno));
}
