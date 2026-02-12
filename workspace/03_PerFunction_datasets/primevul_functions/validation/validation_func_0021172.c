put_node(
    FILE	*fd,
    wordnode_T	*node,
    int		idx,
    int		regionmask,
    int		prefixtree)
{
    int		newindex = idx;
    int		siblingcount = 0;
    wordnode_T	*np;
    int		flags;


    if (node == NULL)
	return 0;


    node->wn_u1.index = idx;


    for (np = node; np != NULL; np = np->wn_sibling)
	++siblingcount;


    if (fd != NULL)
	putc(siblingcount, fd);


    for (np = node; np != NULL; np = np->wn_sibling)
    {
	if (np->wn_byte == 0)
	{
	    if (fd != NULL)
	    {

		if (prefixtree)
		{


		    if (np->wn_flags == (short_u)PFX_FLAGS)
			putc(BY_NOFLAGS, fd);
		    else
		    {
			putc(BY_FLAGS, fd);
			putc(np->wn_flags, fd);
		    }
		    putc(np->wn_affixID, fd);
		    put_bytes(fd, (long_u)np->wn_region, 2);
		}
		else
		{

		    flags = np->wn_flags;
		    if (regionmask != 0 && np->wn_region != regionmask)
			flags |= WF_REGION;
		    if (np->wn_affixID != 0)
			flags |= WF_AFX;
		    if (flags == 0)
		    {

			putc(BY_NOFLAGS, fd);
		    }
		    else
		    {
			if (np->wn_flags >= 0x100)
			{
			    putc(BY_FLAGS2, fd);
			    putc(flags, fd);
			    putc((unsigned)flags >> 8, fd);
			}
			else
			{
			    putc(BY_FLAGS, fd);
			    putc(flags, fd);
			}
			if (flags & WF_REGION)
			    putc(np->wn_region, fd);
			if (flags & WF_AFX)
			    putc(np->wn_affixID, fd);
		    }
		}
	    }
	}
	else
	{
	    if (np->wn_child->wn_u1.index != 0
					 && np->wn_child->wn_u2.wnode != node)
	    {

		if (fd != NULL)
		{
		    putc(BY_INDEX, fd);

		    put_bytes(fd, (long_u)np->wn_child->wn_u1.index, 3);
		}
	    }
	    else if (np->wn_child->wn_u2.wnode == NULL)

		np->wn_child->wn_u2.wnode = node;

	    if (fd != NULL)
		if (putc(np->wn_byte, fd) == EOF)
		{
		    EMSG(_(e_write));
		    return 0;
		}
	}
    }


    newindex += siblingcount + 1;


    for (np = node; np != NULL; np = np->wn_sibling)
	if (np->wn_byte != 0 && np->wn_child->wn_u2.wnode == node)
	    newindex = put_node(fd, np->wn_child, newindex, regionmask,
								  prefixtree);

    return newindex;
}
