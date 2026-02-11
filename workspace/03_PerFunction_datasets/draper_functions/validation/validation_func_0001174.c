state_switch_end_struct_or_union (GMarkupParseContext *context,
                                  ParseContext *ctx,
                                  const gchar *element_name,
                                  GError **error)
{
  pop_node (ctx);
  if (ctx->node_stack == NULL)
    {
      state_switch (ctx, STATE_NAMESPACE);
    }
  else
    {
      if (CURRENT_NODE (ctx)->type == G_IR_NODE_STRUCT)
        state_switch (ctx, STATE_STRUCT);
      else if (CURRENT_NODE (ctx)->type == G_IR_NODE_UNION)
        state_switch (ctx, STATE_UNION);
      else if (CURRENT_NODE (ctx)->type == G_IR_NODE_OBJECT)
        state_switch (ctx, STATE_CLASS);
      else
        {
          int line_number, char_number;
          g_markup_parse_context_get_position (context, &line_number, &char_number);
          g_set_error (error,
                       G_MARKUP_ERROR,
                       G_MARKUP_ERROR_INVALID_CONTENT,
                       "Unexpected end tag '%s' on line %d char %d",
                       element_name,
                       line_number, char_number);
          return FALSE;
        }
    }
  return TRUE;
}
