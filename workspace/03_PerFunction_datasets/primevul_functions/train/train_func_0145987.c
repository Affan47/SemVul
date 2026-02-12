While_Obj Parser::parse_while_directive()
  {
    stack.push_back(Scope::Control);
    bool root = block_stack.back()->is_root();

    While_Obj call = SASS_MEMORY_NEW(While, pstate, 0, 0);

    Expression_Obj predicate = parse_list();
    List_Obj l = Cast<List>(predicate);
    if (!predicate || (l && !l->length())) {
      css_error("Invalid CSS", " after ", ": expected expression (e.g. 1px, bold), was ", false);
    }
    call->predicate(predicate);

    call->block(parse_block(root));

    stack.pop_back();

    return call.detach();
  }
