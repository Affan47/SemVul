reshPackBufferCreate(char **packBuffer, int *packBufferSize, void *context)
{
  int i, packBufferPos = 0;
  int start = START, end = END, sep = SEPARATOR, type;
  listElem_t * curr;

  xassert ( packBuffer );

  LIST_LOCK();

  int nsp = namespaceGetActive ();

  int pBSize = *packBufferSize = getPackBufferSize(context);
  char *pB = *packBuffer = xcalloc(1, *packBufferSize);

  {
    int header[3] = { start, nsp, sep };
    serializePack(header, 3,  DATATYPE_INT, pB, pBSize, &packBufferPos, context);
  }

  for ( i = 0; i < resHList[nsp].size; i++ )
    if ( resHList[nsp].resources[i].val )
      if ( resHList[nsp].resources[i].status == ASSIGNED )
        {
          curr = resHList[nsp].resources + i;
          xassert ( curr->ops );

          type = curr->ops->valTxCode ();

          if ( ! type ) continue;

          serializePack( &type, 1, DATATYPE_INT, * packBuffer,
			    * packBufferSize, &packBufferPos, context);

          curr->ops->valPack(curr->val, pB, pBSize, &packBufferPos, context);

          serializePack(&sep, 1, DATATYPE_INT, pB, pBSize, &packBufferPos, context);

          curr->status = CLOSED;
        }

  LIST_UNLOCK();

  serializePack(&end, 1,  DATATYPE_INT, pB, pBSize, &packBufferPos, context);
}
