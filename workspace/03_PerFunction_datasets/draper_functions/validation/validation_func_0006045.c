insert(Object *obj)
{
	DLinkedListNode *n = allocNode();
	n->obj = obj;
	n->next = NULL;
	if (last) {
		last->next = n;
		n->prev = last;
		last = n;
	} else {
		first = last = n;
	}
	ecount++;
	notifyInsertOrSet(obj);
	return nativeToHandle(n);
}
