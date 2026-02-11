free_index(IndexPtr idx)
{
    free(idx->wd);
    free(idx->pos);
    if (idx->ptruse)
	free(idx->ptruse);
    free(idx->offset);
    free(idx);
}
