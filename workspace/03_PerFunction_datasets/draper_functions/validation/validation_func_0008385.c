IoSeq_newWithUArray_copy_(void *state, UArray *ba, int copy)
{
	IoSeq *self = IoSeq_new(state);

	if (copy)
	{
		UArray_copy_(DATA(self), ba);
	}
	else
	{
		UArray_free(DATA(self));
		IoObject_setDataPointer_(self, ba);
	}

	return self;
}
