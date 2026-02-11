GetFirst(Iterator *it)
{
	struct BitstringIterator *bi = (struct BitstringIterator *)it;

	if (bi == NULL) {
		NullPtrError("GetFirst");
		return NULL;
	}
	if (bi->Bits->count == 0)
		return NULL;
	bi->index = 0;
	return GetNext(it);
}
