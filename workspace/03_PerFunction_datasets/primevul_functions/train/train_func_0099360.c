mark_error (GMarkupParseContext *context,
            GError              *error)
{
  context->state = STATE_ERROR;

  if (context->parser->error)
    (*context->parser->error) (context, error, context->user_data);


  while (context->subparser_stack)
    {
      pop_subparser_stack (context);
      context->awaiting_pop = FALSE;

      if (context->parser->error)
        (*context->parser->error) (context, error, context->user_data);
    }
}
