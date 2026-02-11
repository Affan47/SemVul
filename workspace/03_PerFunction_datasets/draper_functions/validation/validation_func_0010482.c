grammar_symbol_append (symbol *sym, location loc)
{
  symbol_list *p = symbol_list_sym_new (sym, loc);

  if (grammar_end)
    grammar_end->next = p;
  else
    grammar = p;

  grammar_end = p;


  if (sym)
    ++nritems;

  return p;
}
