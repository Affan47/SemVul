prepend(const pointer &sp)
{
    if (nchild >= nchild_max)
    {
	size_t new_nchild_max = nchild_max * 2 + 4;
	pointer *new_child = new pointer [new_nchild_max];
	for (size_t j = 0; j < nchild; ++j)
	    new_child[j + 1] = child[j];
	delete [] child;
	child = new_child;
	nchild_max = new_nchild_max;
    }
    else
    {
	for (size_t j = nchild; j > 0; --j)
	    child[j] = child[j - 1];
    }
    nchild++;
    child[0] = sp;
}
