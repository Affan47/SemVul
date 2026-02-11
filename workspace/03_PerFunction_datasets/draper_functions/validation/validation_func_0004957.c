freeLinkedList(linkedList *l, void (*destructor)(void *e))
{

  listNode *thisNode = l->head;
  while (thisNode)
  {
    listNode *tmp = thisNode->next;
    if (destructor) destructor(thisNode->data);
    free(thisNode);
    thisNode = tmp;
  }
  freeStack(l->deadNodes, free);
  free(l);
}
