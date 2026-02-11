DeleteIterator(Iterator * it)
{
    struct ListIterator *li;
    List           *L;

    if (it == NULL) {
        return NullPtrError("DeleteIterator");
    }
    li = (struct ListIterator *) it;
    L = li->L;
    L->Allocator->free(it);
    return 1;
}
