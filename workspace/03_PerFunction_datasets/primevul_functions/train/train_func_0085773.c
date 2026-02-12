String string_escape_shell_cmd(const char *str) {
  register int x, y, l;
  char *cmd;
  char *p = nullptr;

  l = strlen(str);
  String ret(safe_address(l, 2, 1), ReserveString);
  cmd = ret.bufferSlice().ptr;

  for (x = 0, y = 0; x < l; x++) {
    switch (str[x]) {
    case '"':
    case '\'':
      if (!p && (p = (char *)memchr(str + x + 1, str[x], l - x - 1))) {

      } else if (p && *p == str[x]) {
        p = nullptr;
      } else {
        cmd[y++] = '\\';
      }
      cmd[y++] = str[x];
      break;
    case '#':
    case '&':
    case ';':
    case '`':
    case '|':
    case '*':
    case '?':
    case '~':
    case '<':
    case '>':
    case '^':
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case '$':
    case '\\':
    case '\x0A':
    case '\xFF':
      cmd[y++] = '\\';

    default:
      cmd[y++] = str[x];
    }
  }
  ret.setSize(y);
  return ret;
}
