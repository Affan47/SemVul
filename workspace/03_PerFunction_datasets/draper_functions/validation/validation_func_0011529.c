getTA(unsigned long iaid)
{
    SPtr<TAddrIA> ta;
    this->Client->firstTA();
    while (ta = this->Client->getTA() ) {
	if (ta->getIAID() == iaid)
	    return ta;
    }
    return 0;
}
