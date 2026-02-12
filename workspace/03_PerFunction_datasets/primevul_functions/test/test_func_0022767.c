void lex_unlock_plugins(LEX *lex)
{
  DBUG_ENTER("lex_unlock_plugins");


  if (lex->plugins.elements)
  {
    plugin_unlock_list(0, (plugin_ref*)lex->plugins.buffer,
                       lex->plugins.elements);
  }
  reset_dynamic(&lex->plugins);
  DBUG_VOID_RETURN;
}
