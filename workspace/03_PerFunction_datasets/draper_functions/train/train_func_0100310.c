AddMemo(struct MemoInfo *mptr, struct Memo *memoptr)

{


	memoptr->next = NULL;

	if (!mptr->memos)
	{
		mptr->memos = mptr->lastmemo = memoptr;
		mptr->prev = NULL;
	}
	else
	{
		mptr->lastmemo->next = memoptr;
		memoptr->prev = mptr->lastmemo;
		mptr->lastmemo = memoptr;
	}
}
