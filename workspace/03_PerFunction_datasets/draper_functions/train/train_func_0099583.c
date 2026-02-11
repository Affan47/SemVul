canSample(StochasticNode *snode, Graph const &graph)
{
    switch (getDist(snode)) {
    case GAMMA: case EXP: case CHISQ:


	break;
    default:
	return false;
    }

    GraphView gv(vector<StochasticNode*>(1,snode), graph);


    vector<StochasticNode const*> const &stoch_nodes =
	gv.stochasticChildren();
    for (unsigned int i = 0; i < stoch_nodes.size(); ++i) {
	if (isBounded(stoch_nodes[i])) {
	    return false;
	}
	switch(getDist(stoch_nodes[i])) {
	case EXP: case POIS:
	    break;
	case GAMMA: case NORM: case DEXP: case WEIB: case LNORM:
	    if (gv.isDependent(stoch_nodes[i]->parents()[0])) {
		return false;
	    }
	    break;
	default:
	    return false;
	}
    }


    if (!checkScale(&gv, false)) {
	return false;
    }
    return true;
}
