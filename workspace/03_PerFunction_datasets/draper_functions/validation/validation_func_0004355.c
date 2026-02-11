po_next_message (po_message_iterator_t iterator)
{
  if (iterator->mlp != NULL && iterator->index < iterator->mlp->nitems)
    return (po_message_t) iterator->mlp->item[iterator->index++];
  else
    return NULL;
}
