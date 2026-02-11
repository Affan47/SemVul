_g_ir_parser_parse_string (GIrParser           *parser,
			   const gchar         *namespace,
			   const gchar         *filename,
			   const gchar         *buffer,
			   gssize               length,
			   GError             **error)
{
  ParseContext ctx = { 0 };
  GMarkupParseContext *context;

  ctx.parser = parser;
  ctx.state = STATE_START;
  ctx.file_path = filename;
  ctx.namespace = namespace;
  ctx.include_modules = NULL;
  ctx.aliases = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
  ctx.disguised_structures = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
  ctx.type_depth = 0;
  ctx.dependencies = NULL;
  ctx.current_module = NULL;

  context = g_markup_parse_context_new (&firstpass_parser, 0, &ctx, NULL);

  if (!g_markup_parse_context_parse (context, buffer, length, error))
    goto out;

  if (!g_markup_parse_context_end_parse (context, error))
    goto out;

  g_markup_parse_context_free (context);

  ctx.state = STATE_START;
  context = g_markup_parse_context_new (&markup_parser, 0, &ctx, NULL);
  if (!g_markup_parse_context_parse (context, buffer, length, error))
    goto out;

  if (!g_markup_parse_context_end_parse (context, error))
    goto out;

  parser->parsed_modules = g_list_concat (g_list_copy (ctx.modules),
					  parser->parsed_modules);

 out:

  if (ctx.modules == NULL)
    {


      if (ctx.aliases != NULL)
	g_hash_table_destroy (ctx.aliases);
      if (ctx.disguised_structures != NULL)
	g_hash_table_destroy (ctx.disguised_structures);
      g_list_free (ctx.include_modules);
    }

  g_markup_parse_context_free (context);

  if (ctx.modules)
    return ctx.modules->data;

  if (error && *error == NULL)
    g_set_error (error,
                 G_MARKUP_ERROR,
                 G_MARKUP_ERROR_INVALID_CONTENT,
                 "Expected namespace element in the gir file");
  return NULL;
}
