const_item() const
{
  return thd->lex->context_analysis_only ? FALSE : const_item_cache;
}
