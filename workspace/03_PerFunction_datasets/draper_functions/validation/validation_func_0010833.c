setlayout(const Arg *arg) {
	if(!arg || !arg->v || arg->v != selmon->lt[selmon->sellt])
		selmon->sellt ^= 1;
	if(arg && arg->v)
		selmon->lt[selmon->sellt] = selmon->lts[selmon->curtag] = (Layout *)arg->v;
	strncpy(selmon->ltsymbol, selmon->lt[selmon->sellt]->symbol, sizeof selmon->ltsymbol);
	if(selmon->sel)
		arrange(selmon);
	else
		drawbar(selmon);
}
