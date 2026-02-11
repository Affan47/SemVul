S_CLEAR_WEAKREFR (symbolS *s)
{
  if (LOCAL_SYMBOL_CHECK (s))
    return;
  s->sy_flags.sy_weakrefr = 0;
}
