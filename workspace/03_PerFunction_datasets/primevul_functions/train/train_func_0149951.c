DEFFUNC_llExecFunc(flushRptdMsgsActions)
{
	action_t *pAction = (action_t*) pData;
	assert(pAction != NULL);

	BEGINfunc
	LockObj(pAction);


	if (pAction->f_prevcount && time(NULL) >= REPEATTIME(pAction)) {
		DBGPRINTF("flush %s: repeated %d times, %d sec.\n",
		    module.GetStateName(pAction->pMod), pAction->f_prevcount,
		    repeatinterval[pAction->f_repeatcount]);
		actionWriteToAction(pAction);
		BACKOFF(pAction);
	}
	UnlockObj(pAction);

	ENDfunc
	return RS_RET_OK;
}
