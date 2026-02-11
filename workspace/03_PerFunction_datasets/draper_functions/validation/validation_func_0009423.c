_cmsSubAllocDestroy(_cmsSubAllocator* sub)
{
    _cmsSubAllocator_chunk *chunk, *n;

    for (chunk = sub ->h; chunk != NULL; chunk = n) {

        n = chunk->next;
        if (chunk->Block != NULL) _cmsFree(sub ->ContextID, chunk->Block);
        _cmsFree(sub ->ContextID, chunk);
    }


    _cmsFree(sub ->ContextID, sub);
}
