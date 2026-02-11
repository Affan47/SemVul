make_mode(const unsigned int lmstate)
{
	switch (lmstate) {
	case LM_ST_UNLOCKED:
		return DLM_LOCK_NL;
	case LM_ST_EXCLUSIVE:
		return DLM_LOCK_EX;
	case LM_ST_DEFERRED:
		return DLM_LOCK_CW;
	case LM_ST_SHARED:
		return DLM_LOCK_PR;
	}
	pr_err("unknown LM state %d\n", lmstate);
	BUG();
	return -1;
}
