String_Obj Parser::parse_interpolated_chunk(Token chunk, bool constant, bool css)
  {
    const char* i = chunk.begin;

    const char* p = constant ? find_first_in_interval< exactly<hash_lbrace> >(i, chunk.end) :
                    find_first_in_interval< exactly<hash_lbrace>, block_comment >(i, chunk.end);

    if (!p) {
      String_Quoted* str_quoted = SASS_MEMORY_NEW(String_Quoted, pstate, std::string(i, chunk.end), 0, false, false, true, css);
      if (!constant && str_quoted->quote_mark()) str_quoted->quote_mark('*');
      return str_quoted;
    }

    String_Schema_Obj schema = SASS_MEMORY_NEW(String_Schema, pstate, 0, css);
    schema->is_interpolant(true);
    while (i < chunk.end) {
      p = constant ? find_first_in_interval< exactly<hash_lbrace> >(i, chunk.end) :
          find_first_in_interval< exactly<hash_lbrace>, block_comment >(i, chunk.end);
      if (p) {
        if (i < p) {

          schema->append(SASS_MEMORY_NEW(String_Constant, pstate, std::string(i, p), css));
        }


        if (peek < sequence < optional_spaces, exactly<rbrace> > >(p+2)) { position = p+2;
          css_error("Invalid CSS", " after ", ": expected expression (e.g. 1px, bold), was ");
        }
        const char* j = skip_over_scopes< exactly<hash_lbrace>, exactly<rbrace> >(p + 2, chunk.end);
        if (j) { --j;

          Expression_Obj interp_node = Parser::from_token(Token(p+2, j), ctx, traces, pstate, source).parse_list();
          interp_node->is_interpolant(true);
          schema->append(interp_node);
          i = j;
        }
        else {

          error("unterminated interpolant inside string constant " + chunk.to_string());
        }
      }
      else {

        if (i < chunk.end) schema->append(SASS_MEMORY_NEW(String_Constant, pstate, std::string(i, chunk.end), css));
        break;
      }
      ++ i;
    }

    return schema.detach();
  }
