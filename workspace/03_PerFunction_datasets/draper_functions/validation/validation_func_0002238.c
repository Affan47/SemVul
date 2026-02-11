json_scanner_msg_handler (JsonScanner *scanner,
                          gchar       *message)
{
  JsonParser *parser = scanner->user_data;
  JsonParserPrivate *priv = parser->priv;
  GError *error = NULL;


  g_set_error (&error, JSON_PARSER_ERROR,
               priv->error_code,
               _("%s:%d:%d: Parse error: %s"),
               priv->is_filename ? priv->filename : "<data>",
               scanner->line,
               scanner->position,
               message);

  parser->priv->last_error = error;
  g_signal_emit (parser, parser_signals[ERROR], 0, error);
}
