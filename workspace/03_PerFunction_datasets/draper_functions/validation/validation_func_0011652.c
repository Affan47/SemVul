create (double fr, unsigned int hl, unsigned int np)
{
    Resampler_table *P;

    _mutex.lock ();
    P = _list;
    while (P)
    {
	if ((fr >= P->_fr * 0.999) && (fr <= P->_fr * 1.001) && (hl == P->_hl) && (np == P->_np))
	{
	    P->_refc++;
            _mutex.unlock ();
            return P;
	}
	P = P->_next;
    }
    P = new Resampler_table (fr, hl, np);
    P->_refc = 1;
    P->_next = _list;
    _list = P;
    _mutex.unlock ();
    return P;
}
