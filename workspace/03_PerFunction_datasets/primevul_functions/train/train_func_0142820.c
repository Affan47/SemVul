Selector_Schema_Obj Parser::parse_selector_schema(const char* end_of_selector, bool chroot)
  {
    NESTING_GUARD(nestings);

    lex< optional_spaces >();
    const char* i = position;

    String_Schema* schema = SASS_MEMORY_NEW(String_Schema, pstate);

    Selector_Schema_Obj selector_schema = SASS_MEMORY_NEW(Selector_Schema, pstate, schema);
    selector_schema->connect_parent(chroot == false);
    selector_schema->media_block(last_media_block);


    while (i < end_of_selector) {

      if (const char* p = find_first_in_interval< exactly<hash_lbrace>, block_comment >(i, end_of_selector)) {

        if (i < p) {
          std::string parsed(i, p);
          String_Constant_Obj str = SASS_MEMORY_NEW(String_Constant, pstate, parsed);
          pstate += Offset(parsed);
          str->update_pstate(pstate);
          schema->append(str);
        }


        const char* j = skip_over_scopes< exactly<hash_lbrace>, exactly<rbrace> >(p + 2, end_of_selector);

        if (!j || peek < sequence < optional_spaces, exactly<rbrace> > >(p+2)) {
          position = p+2;
          css_error("Invalid CSS", " after ", ": expected expression (e.g. 1px, bold), was ");
        }

        pstate.add(p, p+2);
        Expression_Obj interpolant = Parser::from_c_str(p+2, j, ctx, traces, pstate).parse_list();

        interpolant->is_interpolant(true);


        schema->append(interpolant);

        pstate.add(p+2, j);

        i = j;
      }


      else {

        if (i < end_of_selector) {
          std::string parsed(i, end_of_selector);
          String_Constant_Obj str = SASS_MEMORY_NEW(String_Constant, pstate, parsed);
          pstate += Offset(parsed);
          str->update_pstate(pstate);
          i = end_of_selector;
          schema->append(str);
        }

      }
    }


    position = i;


    selector_schema->update_pstate(pstate);
    schema->update_pstate(pstate);

    after_token = before_token = pstate;


    return selector_schema.detach();
  }
