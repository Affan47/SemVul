improveCrossings(void)
{
    const double crossing_penalty = routingPenalty(crossingPenalty);
    const double shared_path_penalty = routingPenalty(fixedSharedPathPenalty);
    if ((crossing_penalty == 0) && (shared_path_penalty == 0))
    {

        return;
    }


    _inCrossingPenaltyReroutingStage = true;
    ConnRefSet crossingConns;
    ConnRefList::iterator fin = connRefs.end();
    for (ConnRefList::iterator i = connRefs.begin(); i != fin; ++i)
    {
        Avoid::Polygon& iRoute = (*i)->routeRef();
        ConnRefList::iterator j = i;
        for (++j; j != fin; ++j)
        {
            if ((crossingConns.find(*i) != crossingConns.end()) &&
                    (crossingConns.find(*j) != crossingConns.end()))
            {

                continue;
            }

            Avoid::Polygon& jRoute = (*j)->routeRef();
            CrossingsInfoPair crossingInfo = std::make_pair(0, 0);
            bool meetsPenaltyCriteria = false;
            for (size_t jInd = 1; jInd < jRoute.size(); ++jInd)
            {
                const bool finalSegment = ((jInd + 1) == jRoute.size());
                CrossingsInfoPair crossingInfo = countRealCrossings(
                        iRoute, true, jRoute, jInd, false,
                        finalSegment, NULL, NULL, *i, *j);

                if ((shared_path_penalty > 0) &&
                    (crossingInfo.second & CROSSING_SHARES_PATH) &&
                    (crossingInfo.second & CROSSING_SHARES_FIXED_SEGMENT) &&
                    !(crossingInfo.second & CROSSING_SHARES_PATH_AT_END))
                {


                    meetsPenaltyCriteria = true;
                    break;
                }
                else if ((crossing_penalty > 0) && (crossingInfo.first > 0))
                {

                    meetsPenaltyCriteria = true;
                    break;
                }
            }
            if (meetsPenaltyCriteria)
            {
                crossingConns.insert(*i);
                crossingConns.insert(*j);
            }
        }
    }

    for (ConnRefSet::iterator i = crossingConns.begin();
            i != crossingConns.end(); ++i)
    {
        ConnRef *conn = *i;
        conn->makePathInvalid();


    }
    for (ConnRefSet::iterator i = crossingConns.begin();
            i != crossingConns.end(); ++i)
    {
        ConnRef *conn = *i;
        conn->generatePath();
    }
    _inCrossingPenaltyReroutingStage = false;
}
