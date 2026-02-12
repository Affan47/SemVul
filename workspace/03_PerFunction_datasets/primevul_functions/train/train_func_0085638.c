static int _php_mbstr_parse_mail_headers(Array &ht, const char *str,
                                         size_t str_len) {
  const char *ps;
  size_t icnt;
  int state = 0;
  int crlf_state = -1;

  StringBuffer token;
  String fld_name, fld_val;

  ps = str;
  icnt = str_len;


  while (icnt > 0) {
    switch (*ps) {
    case ':':
      if (crlf_state == 1) {
        token.append('\r');
      }

      if (state == 0 || state == 1) {
        fld_name = token.detach();

        state = 2;
      } else {
        token.append(*ps);
      }

      crlf_state = 0;
      break;

    case '\n':
      if (crlf_state == -1) {
        goto out;
      }
      crlf_state = -1;
      break;

    case '\r':
      if (crlf_state == 1) {
        token.append('\r');
      } else {
        crlf_state = 1;
      }
      break;

    case ' ': case '\t':
      if (crlf_state == -1) {
        if (state == 3) {

          state = 4;
        } else {

          state = 5;
        }
      } else {
        if (crlf_state == 1) {
          token.append('\r');
        }
        if (state == 1 || state == 3) {
          token.append(*ps);
        }
      }
      crlf_state = 0;
      break;

    default:
      switch (state) {
      case 0:
        token.clear();
        state = 1;
        break;

      case 2:
        if (crlf_state != -1) {
          token.clear();
          state = 3;
          break;
        }


      case 3:
        if (crlf_state == -1) {
          fld_val = token.detach();
          if (!fld_name.empty() && !fld_val.empty()) {


            ht.set(HHVM_FN(strtoupper)(fld_name), fld_val);
          }
          state = 1;
        }
        break;

      case 4:
        token.append(' ');
        state = 3;
        break;
      }

      if (crlf_state == 1) {
        token.append('\r');
      }

      token.append(*ps);

      crlf_state = 0;
      break;
    }
    ps++, icnt--;
  }
out:
  if (state == 2) {
    token.clear();
    state = 3;
  }
  if (state == 3) {
    fld_val = token.detach();
    if (!fld_name.empty() && !fld_val.empty()) {


      ht.set(HHVM_FN(strtoupper)(fld_name), fld_val);
    }
  }
  return state;
}
