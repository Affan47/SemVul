Lookahead Parser::lookahead_for_value(const char* start)
  {

    Lookahead rv = Lookahead();

    const char* p = start ? start : position;

    if (const char* q =
      peek <
        non_greedy <
          alternatives <

            block_comment,

            sequence <
              interpolant,
              optional <
                quoted_string
              >
            >,
            identifier,
            variable,

            sequence <
              parenthese_scope,
              interpolant,
              optional <
                quoted_string
              >
            >
          >,
          sequence <

            alternatives <

              exactly<'{'>,
              exactly<'}'>,
              exactly<';'>
            >
          >
        >
      >(p)
    ) {
      if (p == q) return rv;
      while (p < q) {

        if (*p == '#' && *(p+1) == '{') {
          rv.has_interpolants = true;
          p = q; break;
        }
        ++ p;
      }

      rv.position = q;

      if (peek < exactly<'{'> >(q)) rv.found = q;
      else if (peek < exactly<';'> >(q)) rv.found = q;
      else if (peek < exactly<'}'> >(q)) rv.found = q;
    }

    return rv;
  }
}
