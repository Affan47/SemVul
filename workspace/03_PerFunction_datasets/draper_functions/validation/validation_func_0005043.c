create(const char fmt[],va_list& args)
{
  const GP<GStringRep> s(create(fmt));
  return (s?(s->vformat(args)):s);
}
