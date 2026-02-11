EndPDDeclaration()
{
    if (!this->PDLst.count()) {
	Log(Crit) << "No PD pools defined ." << LogEnd;
	return false;
    }
    if (!this->PDPrefix) {
	Log(Crit) << "PD prefix length not defined or set to 0." << LogEnd;
	return false;
    }

    int len = 0;
    this->PDLst.first();
    while ( SPtr<TStationRange> pool = PDLst.get() ) {
	if (!len)
	    len = pool->getPrefixLength();
	if (len!=pool->getPrefixLength()) {
	    Log(Crit) << "Prefix pools with different lengths are not supported. Make sure that all 'pd-pool' uses the same prefix length." << LogEnd;
	    return false;
	}
    }
    if (len>PDPrefix) {
	Log(Crit) << "Clients are supposed to get /" << this->PDPrefix << " prefixes, but pd-pool(s) are only /" << len << " long." << LogEnd;
	return false;
    }
    if (len==PDPrefix) {
	Log(Warning) << "Prefix pool /" << PDPrefix << " defined and clients are supposed to get /" << len << " prefixes. Only ONE client will get prefix" << LogEnd;
    }

    SPtr<TSrvCfgPD> ptrPD = new TSrvCfgPD();
    ParserOptStack.getLast()->setPool(&this->PDLst);
    if (!ptrPD->setOptions(ParserOptStack.getLast(), this->PDPrefix))
	return false;
    SrvCfgPDLst.append(ptrPD);


    ParserOptStack.delLast();
    return true;
}
