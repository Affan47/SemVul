AsnListAppend PARAMS( (list),
AsnList* list )
{
    AsnListNode* newNode;
    void*      dataAddr;

    newNode  = (AsnListNode *) Asn1Alloc( sizeof(AsnListNode) + list->dataSize );
    dataAddr = (void *) &(newNode->data);

    newNode->next = NULL;

    if( list->last == NULL )
        {
        newNode->prev = NULL;
        list->first   = list->last = newNode;
        }
    else
        {
        newNode->prev     = list->last;
        list->last->next  = newNode;
        list->last        = newNode;
        }

    list->curr = newNode;
    list->count++;

    return( dataAddr );
}
