ilSetMemory(mAlloc AllocFunc, mFree FreeFunc)
{
	ialloc_ptr = AllocFunc == NULL ? DefaultAllocFunc : AllocFunc;
	ifree_ptr = FreeFunc == NULL ? DefaultFreeFunc : FreeFunc;
}
