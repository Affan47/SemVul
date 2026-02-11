FindSymbol(Symbol* sym)
{
    const Symbol* res = NULL;
    for (std::vector<SymTable*>::reverse_iterator it = sym_table_stack.rbegin();
         it != sym_table_stack.rend() && res == NULL; ++it)
    {
        res = (*it)->Find(sym);
    }
    return res;
}
