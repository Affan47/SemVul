lineeditor_output
   ___P((___device_tty *self,
         ___C *buf,
         int len),
        (self,
         buf,
         len)
___device_tty *self;
___C *buf;
int len;)
{


  ___device_tty *d = self;
  ___SCMOBJ e;

#ifdef ___DEBUG_TTY

  {
    int i;

    ___printf ("et:%d row:%2d col:%2d cursor:%2d dw:%d len:%3d  ",
               d->emulate_terminal,
               d->terminal_row,
               d->terminal_col,
               d->terminal_cursor,
               d->terminal_delayed_wrap,
               len);

    ___printf ("\"");

    for (i=0; i<len; i++)
      if (buf[i] < 32 || buf[i] >= 127)
        ___printf ("\\x%02x", buf[i]);
      else
        ___printf ("%c", buf[i]);

    ___printf ("\"\n");
  }

#endif

  if (d->emulate_terminal)
    {
      d->emulate_terminal = 0;
      e = lineeditor_output_terminal_emulate (d, buf, len);
      d->emulate_terminal = 1;
    }
  else
    e = extensible_string_insert
          (&d->output_char,
           d->output_char.length,
           len,
           buf);

#ifdef USE_WIN32
  e = lineeditor_output_drain (d);
#endif

  return e;
}
