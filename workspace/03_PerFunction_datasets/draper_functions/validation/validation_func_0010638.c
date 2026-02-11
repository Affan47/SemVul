finish_handler (tree handler)
{
  if (!processing_template_decl)
    expand_end_catch_block ();
  do_poplevel ();
  RECHAIN_STMTS (handler, HANDLER_BODY (handler));
}
