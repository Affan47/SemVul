Mixin_Call_Obj Parser::parse_include_directive()
  {

    lex_identifier();

    std::string name(Util::normalize_underscores(lexed));

    Mixin_Call_Obj call = SASS_MEMORY_NEW(Mixin_Call, pstate, name, {}, {}, {});

    call->arguments(parse_arguments());

    bool has_parameters = lex< kwd_using >() != nullptr;

    if (has_parameters) {
      if (!peek< exactly<'('> >()) css_error("Invalid CSS", " after ", ": expected \"(\", was ");
    } else {
      if (peek< exactly<'('> >()) css_error("Invalid CSS", " after ", ": expected \";\", was ");
    }

    if (has_parameters) call->block_parameters(parse_parameters());

    if (peek < exactly <'{'> >()) {
      call->block(parse_block());
    }
    else if (has_parameters)  {
      css_error("Invalid CSS", " after ", ": expected \"{\", was ");
    }

    return call.detach();
  }
}
}
