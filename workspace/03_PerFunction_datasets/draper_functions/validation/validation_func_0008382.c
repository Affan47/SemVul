dico_strategy_dup(const dico_strategy_t strat)
{
    dico_strategy_t np = dico_strategy_create(strat->name, strat->descr);
    if (np) {
	np->sel = strat->sel;
	np->closure = strat->closure;
    }
    return np;
}
