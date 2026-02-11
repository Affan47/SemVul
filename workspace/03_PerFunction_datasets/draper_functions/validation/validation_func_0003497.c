generateRoutingDAGInternalNodes(RoutingDAG *rDAG, const std::vector<double> &rnps, double quadrantAngularWidth)
{
    unsigned int numLayers = 0;
    double maxrnp = *max_element(rnps.begin(), rnps.end());
    std::cout << "maxrnp initialized: " << maxrnp << std::endl;
    maxrnp = (maxrnp > 0) ? maxrnp : 1;
    std::cout << "Found maxrnp = " << maxrnp << std::endl;
    if(liftedoRadius - liftediRadius > maxrnp * 4)
    {
        numLayers = (int)floor( (liftedoRadius - liftediRadius) / (maxrnp*3) );
    }
    std::cout << "Found numLayers = " << numLayers << std::endl;

    for(unsigned int i=1; i<=numLayers; i++)
    {
        if (i % 5000 == 0)
        {
            std::cout << "Current layer is: " << i << std::endl;
        }

        double layerHeight = oHeight - (oHeight - iHeight) * i / (numLayers + 1);
        double layerRadius = oRadius - (oRadius - iRadius) * i / (numLayers + 1);

        double layerLength = quadrantAngularWidth*layerRadius;

        int numNodesLayer = (int) floor( layerLength / (2* maxrnp + 2) );
        double startingAngle = angle + quadrantAngularWidth / (2 * numNodesLayer);
        for(int j=0; j<numNodesLayer; j++)
        {
            double tempAngle = startingAngle+j*PI/(2*numNodesLayer);

            Node* tempNode = new Node(centerX+layerRadius*cos(tempAngle), centerY+layerRadius*sin(tempAngle), layerHeight, INTERNAL_NODE);
            tempNode->setLayer(i);
            tempNode->setLayerIndex(j);
            rDAG->insertNode(tempNode);
        }
    }
    rDAG->setNumLayers(numLayers+2);
    rDAG->setNodesReadInStatus(NODES_READ_IN);
}
