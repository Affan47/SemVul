Create(size_t elementsize)
{
    Deque * d = CurrentAllocator->malloc(sizeof(struct deque_t));
    if (d == NULL)	{
    	iError.RaiseError("iDeque.Create",CONTAINER_ERROR_BADARG);
    	return NULL;
    }
    return Init(d,elementsize);
}
