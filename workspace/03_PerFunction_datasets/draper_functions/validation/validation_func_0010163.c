gamgi_engine_iarray_pop (gamgi_iarray *iarray, int offset)
{


iarray->offset = offset;

if (offset == 0) iarray->last = NULL;
else iarray->last = iarray->array + (offset - 1) * iarray->dimension;
}
