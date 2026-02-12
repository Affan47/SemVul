tree_add_word(
    spellinfo_T	*spin,
    char_u	*word,
    wordnode_T	*root,
    int		flags,
    int		region,
    int		affixID)
{
    wordnode_T	*node = root;
    wordnode_T	*np;
    wordnode_T	*copyp, **copyprev;
    wordnode_T	**prev = NULL;
    int		i;


    for (i = 0; ; ++i)
    {


	if (node != NULL && node->wn_refs > 1)
	{
	    --node->wn_refs;
	    copyprev = prev;
	    for (copyp = node; copyp != NULL; copyp = copyp->wn_sibling)
	    {

		np = get_wordnode(spin);
		if (np == NULL)
		    return FAIL;
		np->wn_child = copyp->wn_child;
		if (np->wn_child != NULL)
		    ++np->wn_child->wn_refs;
		np->wn_byte = copyp->wn_byte;
		if (np->wn_byte == NUL)
		{
		    np->wn_flags = copyp->wn_flags;
		    np->wn_region = copyp->wn_region;
		    np->wn_affixID = copyp->wn_affixID;
		}


		np->wn_refs = 1;
		if (copyprev != NULL)
		    *copyprev = np;
		copyprev = &np->wn_sibling;


		if (copyp == node)
		    node = np;
	    }
	}


	while (node != NULL
		&& (node->wn_byte < word[i]
		    || (node->wn_byte == NUL
			&& (flags < 0
			    ? node->wn_affixID < (unsigned)affixID
			    : (node->wn_flags < (unsigned)(flags & WN_MASK)
				|| (node->wn_flags == (flags & WN_MASK)
				    && (spin->si_sugtree
					? (node->wn_region & 0xffff) < region
					: node->wn_affixID
						    < (unsigned)affixID)))))))
	{
	    prev = &node->wn_sibling;
	    node = *prev;
	}
	if (node == NULL
		|| node->wn_byte != word[i]
		|| (word[i] == NUL
		    && (flags < 0
			|| spin->si_sugtree
			|| node->wn_flags != (flags & WN_MASK)
			|| node->wn_affixID != affixID)))
	{

	    np = get_wordnode(spin);
	    if (np == NULL)
		return FAIL;
	    np->wn_byte = word[i];


	    if (node == NULL)
		np->wn_refs = 1;
	    else
	    {
		np->wn_refs = node->wn_refs;
		node->wn_refs = 1;
	    }
	    if (prev != NULL)
		*prev = np;
	    np->wn_sibling = node;
	    node = np;
	}

	if (word[i] == NUL)
	{
	    node->wn_flags = flags;
	    node->wn_region |= region;
	    node->wn_affixID = affixID;
	    break;
	}
	prev = &node->wn_child;
	node = *prev;
    }
#ifdef SPELL_PRINTTREE
    smsg((char_u *)"Added \"%s\"", word);
    spell_print_tree(root->wn_sibling);
#endif


    ++spin->si_msg_count;

    if (spin->si_compress_cnt > 1)
    {
	if (--spin->si_compress_cnt == 1)

	    spin->si_blocks_cnt += compress_inc;
    }


#ifndef SPELL_COMPRESS_ALLWAYS
    if (spin->si_compress_cnt == 1
	    ? spin->si_free_count < MAXWLEN
	    : spin->si_blocks_cnt >= compress_start)
#endif
    {


	spin->si_blocks_cnt -= compress_inc;
	spin->si_compress_cnt = compress_added;

	if (spin->si_verbose)
	{
	    msg_start();
	    msg_puts((char_u *)_(msg_compressing));
	    msg_clr_eos();
	    msg_didout = FALSE;
	    msg_col = 0;
	    out_flush();
	}


	wordtree_compress(spin, spin->si_foldroot);
	if (affixID >= 0)
	    wordtree_compress(spin, spin->si_keeproot);
    }

    return OK;
}
