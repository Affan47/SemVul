setOptions(SPtr<TSrvParsGlobalOpt> opt)
{
    T1Beg    = opt->getT1Beg();
    T2Beg    = opt->getT2Beg();
    T1End    = opt->getT1End();
    T2End    = opt->getT2End();
    PrefBeg  = opt->getPrefBeg();
    PrefEnd  = opt->getPrefEnd();
    ValidBeg = opt->getValidBeg();
    ValidEnd = opt->getValidEnd();
    Share    = opt->getShare();

    allowLst = opt->getAllowClientClassString();
    denyLst = opt->getDenyClientClassString();

    ClassMaxLease = opt->getClassMaxLease();

    SPtr<TStationRange> statRange;
    opt->firstRejedClnt();
    while(statRange=opt->getRejedClnt())
        this->RejedClnt.append(statRange);

    opt->firstAcceptClnt();
    while(statRange=opt->getAcceptClnt())
        this->AcceptClnt.append(statRange);

    opt->firstPool();
    this->Pool = opt->getPool();
    if (opt->getPool()) {
	Log(Warning) << "Two or more pool defined. Only one is used." << LogEnd;
    }


    this->AddrsCount = this->Pool->rangeCount();
    this->AddrsAssigned = 0;

    if (this->ClassMaxLease > this->AddrsCount)
	this->ClassMaxLease = this->AddrsCount;

    AddrParams = opt->getAddrParams();
}
