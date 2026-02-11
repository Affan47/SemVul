handle_text(Seriousness s, const String &text)
{
  _errh->handle_text(s, text);
  if (s >= _exit_seriousness)
    exit(1);
}
