emit_end_element (GMarkupParseContext  *context,
                  GError              **error)
{


  GError *tmp_error = NULL;

  g_assert (context->tag_stack != NULL);

  possibly_finish_subparser (context);


  if ((context->flags & G_MARKUP_IGNORE_QUALIFIED) && strchr (current_element (context), ':'))
    {
      g_markup_parse_context_pop (context);
      pop_tag (context);
      return;
    }

  tmp_error = NULL;
  if (context->parser->end_element)
    (* context->parser->end_element) (context,
                                      current_element (context),
                                      context->user_data,
                                      &tmp_error);

  ensure_no_outstanding_subparser (context);

  if (tmp_error)
    {
      mark_error (context, tmp_error);
      g_propagate_error (error, tmp_error);
    }

  pop_tag (context);
}
