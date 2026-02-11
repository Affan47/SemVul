cp_spacevec(const String &str, Vector<String> &conf)
{

  if (str.length() == 0)
    return;


  const char *s = str.data();
  const char *end = str.end();
  while ((s = cp_skip_comment_space(s, end)) < end) {
    const char *t = skip_spacevec_item(s, end);
    conf.push_back(str.substring(s, t));
    s = t;
  }
}
