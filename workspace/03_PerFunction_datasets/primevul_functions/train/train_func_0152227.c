static Block_Obj sass_parse_block(Sass_Compiler* compiler) throw()
  {


    if (compiler == 0) return {};

    Context* cpp_ctx = compiler->cpp_ctx;
    Sass_Context* c_ctx = compiler->c_ctx;

    compiler->cpp_ctx->c_compiler = compiler;
    compiler->state = SASS_COMPILER_PARSED;

    try {


      std::string input_path = safe_str(c_ctx->input_path);
      std::string output_path = safe_str(c_ctx->output_path);


      bool skip = c_ctx->type == SASS_CONTEXT_DATA;


      Block_Obj root(cpp_ctx->parse());

      if (!root) return {};


      size_t headers = cpp_ctx->head_imports;


      if (copy_strings(cpp_ctx->get_included_files(skip, headers), &c_ctx->included_files) == NULL)
        throw(std::bad_alloc());


      return root;

    }

    catch (...) { handle_errors(c_ctx); }


    return {};

  }
