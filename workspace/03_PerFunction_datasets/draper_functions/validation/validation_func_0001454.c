isFwdPathUnused(
  IBNode *p_node,
  short int dLid,
  map_pnode_p_sint &outPortUsedMap)
{
  int hops = 0;
  IBNode *pNode = p_node;
  stringstream vSt;

  while (hops < 16)
  {
    hops++;


    int portNum = pNode->getLFTPortForLid(dLid);
    if (portNum == IB_LFT_UNASSIGNED)
      return(0);

    vSt << "Out on node:" << pNode->name << " port:" << portNum << endl;


    if (portNum == 0) return(0);

    IBPort *p_port = pNode->getPort(portNum);
    if (!p_port) return(0);


    IBPort *p_remPort = p_port->p_remotePort;
    if (!p_remPort) return(0);


    short int *outPortUsedVec = outPortUsedMap[pNode];
    if (outPortUsedVec[portNum - 1]) return(0);


    if (p_remPort->p_node->type != IB_SW_NODE) return(1);

    pNode = p_remPort->p_node;
  }

  cout << "-E- Found loop on the way to:" << dLid
       << " through:" << pNode->name << endl;
  cout << vSt.str();
  return(0);
}
