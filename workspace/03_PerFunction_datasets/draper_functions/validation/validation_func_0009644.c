freeIntNode(pANTLR3_INT_TRIE_NODE node)
{
    pANTLR3_TRIE_ENTRY	thisEntry;
    pANTLR3_TRIE_ENTRY	nextEntry;


    if (node->bitNum > node->leftN->bitNum)
    {


	freeIntNode(node->leftN);
    }


    if (node->bitNum > node->rightN->bitNum)
    {


	freeIntNode(node->rightN);
    }


    thisEntry	= node->buckets;

    while (thisEntry != NULL)
    {
	nextEntry   = thisEntry->next;


	if (thisEntry->type == ANTLR3_HASH_TYPE_STR && thisEntry->freeptr != NULL)
	{
	    thisEntry->freeptr(thisEntry->data.ptr);
	}


	ANTLR3_FREE(thisEntry);
	thisEntry = nextEntry;
    }


    ANTLR3_FREE(node);


}
