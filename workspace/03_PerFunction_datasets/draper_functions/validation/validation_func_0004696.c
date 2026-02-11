destroyObject(TIMER * pTimer)
{


	TIMER *pObj;


	if (pTimer) {


		for (;;) {
			pObj = pTimer->pointer;
			if (NULL == pObj)
				break;
			free(pTimer);
			pTimer = NULL;
			pTimer = pObj;
		}

		pTimer = NULL;
	}
}
