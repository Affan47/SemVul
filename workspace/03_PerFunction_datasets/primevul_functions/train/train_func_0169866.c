void Item_field::fix_after_pullout(st_select_lex *new_parent, Item **ref)
{
  if (new_parent == get_depended_from())
    depended_from= NULL;
  if (context)
  {
    bool need_change= false;


    for (Name_resolution_context *ct= context; ct; ct= ct->outer_context)
    {
      if (new_parent == ct->select_lex)
      {
        need_change= true;
        break;
      }
    }
    if (!need_change)
      return;

    Name_resolution_context *ctx= new Name_resolution_context();
    if (context->select_lex == new_parent)
    {


      ctx->outer_context= context->outer_context;
    }
    else if (context->outer_context)
    {

      ctx->outer_context= context->outer_context->outer_context;
    }
    else
    {

      ctx->outer_context= NULL;
    }
    ctx->table_list= context->first_name_resolution_table;
    ctx->select_lex= new_parent;
    if (context->select_lex == NULL)
      ctx->select_lex= NULL;
    ctx->first_name_resolution_table= context->first_name_resolution_table;
    ctx->last_name_resolution_table=  context->last_name_resolution_table;
    ctx->error_processor=             context->error_processor;
    ctx->error_processor_data=        context->error_processor_data;
    ctx->resolve_in_select_list=      context->resolve_in_select_list;
    ctx->security_ctx=                context->security_ctx;
    this->context=ctx;
  }
}
