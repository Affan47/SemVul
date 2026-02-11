PrintLosig(ostream& os, const losig* const sig)
{
    if (!sig->NAMECHAIN)
	return os;
    for (struct chain* ch = sig->NAMECHAIN;
	    ch;
	    ch = ch->NEXT)
    {
	os << (char*)(ch->DATA) << " " ;
    }
    os << endl;
    return os;
}
