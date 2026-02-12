Mixin_Call_Obj Parser::parse_include_directive()
  {

    lex_identifier();

    std::string name(Util::normalize_underscores(lexed));

    Mixin_Call_Obj call = SASS_MEMORY_NEW(Mixin_Call, pstate, name, {}, {});

    call->arguments(parse_arguments());

    if (peek < exactly <'{'> >()) {
      call->block(parse_block());
    }

    return call.detach();
  }
}
