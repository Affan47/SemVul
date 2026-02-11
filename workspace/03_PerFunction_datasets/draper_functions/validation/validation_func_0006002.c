calCoef(double *coef, GraphView const *gv,
		    vector<ConjugateDist> const &child_dist, unsigned int chain)
{
    const double xold = gv->nodes()[0]->value(chain)[0];
    vector<StochasticNode const*> const &stoch_children =
        gv->stochasticChildren();
    unsigned long nchildren = stoch_children.size();

    for (unsigned int i = 0; i < nchildren; ++i) {
        coef[i] = -getScale(stoch_children[i], child_dist[i], chain);
    }
    double val = xold + 1;
    gv->setValue(&val, 1, chain);
    for (unsigned int i = 0; i < nchildren; ++i) {
        coef[i] += getScale(stoch_children[i], child_dist[i], chain);
    }
    gv->setValue(&xold, 1, chain);
}
