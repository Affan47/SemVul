to_be_quoted(const char * word, size_t size)
{
  int do_quote;
  const char * cur;
  size_t i;

  do_quote = 0;
  cur = word;
  for(i = 0 ; i < size ; i ++) {
    switch (* cur) {
    case ',':
    case ':':
    case '!':
    case '"':
    case '#':
    case '$':
    case '@':
    case '[':
    case '\\':
    case ']':
    case '^':
    case '`':
    case '{':
    case '|':
    case '}':
    case '~':
    case '=':
    case '?':
    case '_':
      do_quote = 1;
      break;
    default:
      if (((unsigned char) * cur) >= 128)
        do_quote = 1;
      break;
    }
    cur ++;
  }

  return do_quote;
}
