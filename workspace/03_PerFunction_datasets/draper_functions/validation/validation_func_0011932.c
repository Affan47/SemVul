reclaimSymbols(void)
{
    Symbol* sym;
    for(sym=symlist;sym;) {
	Symbol* next = sym->next;
        freeSymbol(sym);
	sym = next;
    }
}
