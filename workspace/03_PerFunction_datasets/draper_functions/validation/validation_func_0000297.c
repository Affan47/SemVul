dfsBackToCAByLftToDLIDs(IBNode *node,
        list<unsigned int> &dstLids,
        unsigned int dstPortNum,
        set<IBNode *> &visitedNodes,
        map<IBPort *, list<unsigned int> > &HCAPortsLids)
{
    if (FabricUtilsVerboseLevel & FABU_LOG_VERBOSE) {
        cout << "-V- Visiting " << node->name << " searching for lids:";
        for (list<unsigned int>::const_iterator lI = dstLids.begin();
                lI != dstLids.end(); lI++) cout << *lI << ",";
        cout << endl;
    }

    if (node->type != IB_SW_NODE) {
        IBPort* port = node->getPort(dstPortNum);
        HCAPortsLids[port] = dstLids;
        return(0);
    }


    list<unsigned int> subDstLids;
    for (list<unsigned int>::const_iterator lI = dstLids.begin();
            lI != dstLids.end(); lI++) {
        unsigned int lid = *lI;
        if ((lid < node->LFT.size()) && (node->LFT[lid] == dstPortNum)) {
            subDstLids.push_front(lid);
        }
    }


    if (subDstLids.size() == 0) {
        if (FabricUtilsVerboseLevel & FABU_LOG_VERBOSE)
            cout << "-V- Dead end" << endl;
        return(0);
    }


    visitedNodes.insert(node);


    for (unsigned int pn = 1; pn <= node->numPorts; pn++) {
        if (pn != dstPortNum) {
            IBPort *port = node->getPort(pn);
            if (!port || ! port->p_remotePort) continue;


            IBNode *p_remNode = port->p_remotePort->p_node;
            if (visitedNodes.find(p_remNode) == visitedNodes.end()) {
                unsigned int remPortNum = port->p_remotePort->num;
                dfsBackToCAByLftToDLIDs(p_remNode, subDstLids, remPortNum,
                        visitedNodes, HCAPortsLids);
            }
        }
    }
    return(0);
}
