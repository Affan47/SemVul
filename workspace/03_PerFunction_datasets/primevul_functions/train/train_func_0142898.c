Lookahead Parser::lookahead_for_selector(const char* start)
  {

    Lookahead rv = Lookahead();

    const char* p = start ? start : position;

    rv.error = p;
    if (const char* q =
      peek <
        re_selector_list
      >(p)
    ) {
      bool could_be_property = peek< sequence< exactly<'-'>, exactly<'-'> > >(p) != 0;
      bool could_be_escaped = false;
      while (p < q) {

        if (*p == '#' && *(p+1) == '{') {
          rv.has_interpolants = true;
          p = q; break;
        }

        if (*p == ':' && !could_be_escaped) {
          rv.is_custom_property = could_be_property || p+1 == q || peek< space >(p+1);
        }
        could_be_escaped = *p == '\\';
        ++ p;
      }

      rv.error = q;
      rv.position = q;

      if (peek < exactly<'{'> >(q)) rv.found = q;

      else if (peek < exactly<'('> >(q)) rv.found = q;

      if (rv.found || *p == 0) rv.error = 0;
    }

    rv.parsable = ! rv.has_interpolants;

    return rv;

  }
}
}
