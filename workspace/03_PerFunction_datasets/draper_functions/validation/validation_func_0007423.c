handle_starttag(void *unused, const string name, pairlist attribs)
{
  conststring id;

  if (copying || is_match(name, attribs)) {
    if (!copying && (id = pairlist_get(attribs, "id")))
      add_href(&attribs, base, id);
    if (!eq(name, "a") && !eq(name, "A")) print_tag(name, attribs, false);
    copying++;
  }
}
