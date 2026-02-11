sumChildrenLength(GraphView const *gv)
{
    vector<StochasticNode const *> const &children =
	gv->stochasticChildren();

    unsigned int N = 0;
    for (unsigned int i = 0; i < children.size(); ++i) {
	N += children[i]->length();
    }
    return N;
}
