static int sass_compile_context (Sass_Context* c_ctx, Context* cpp_ctx)
  {


    Sass_Compiler* compiler = sass_prepare_context(c_ctx, cpp_ctx);

    try {

      sass_compiler_parse(compiler);
      sass_compiler_execute(compiler);
    }

    catch (...) { handle_errors(c_ctx); }

    sass_delete_compiler(compiler);

    return c_ctx->error_status;
  }
