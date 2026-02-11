divergence(unsigned int i, unsigned int j) const
    {
	double div = 0;
	for (unsigned int r = 0; r < _nrep; ++r) {
	    _repnode->randomSample(_rngs[i], i);
	    _repnode->randomSample(_rngs[j], j);
	    div += _repnode->logDensity(i, PDF_FULL) +
		_repnode->logDensity(j, PDF_FULL);
	    _repnode->swapValue(i,j);
	    div -= _repnode->logDensity(i, PDF_FULL) +
		_repnode->logDensity(j, PDF_FULL);
	}
	return div / _nrep;
    }
