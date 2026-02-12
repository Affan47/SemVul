Block_Obj Parser::parse()
  {


    read_bom();


    const char* it = utf8::find_invalid(position, end);


    if (it != end) {
      pstate += Offset::init(position, it);
      traces.push_back(Backtrace(pstate));
      throw Exception::InvalidSass(pstate, traces, "Invalid UTF-8 sequence");
    }


    Block_Obj root = SASS_MEMORY_NEW(Block, pstate, 0, true);


    if (ctx.resources.size() == 1) {

      ctx.apply_custom_headers(root, path, pstate);
    }


    block_stack.push_back(root);
    parse_block_nodes(true);
    block_stack.pop_back();


    root->update_pstate(pstate);

    if (position != end) {
      css_error("Invalid CSS", " after ", ": expected selector or at-rule, was ");
    }

    return root;
  }
