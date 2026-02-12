if(currRefCount == 0)
	{

		if(pThis->pszRawMsg != pThis->szRawMsg)
			free(pThis->pszRawMsg);
		freeTAG(pThis);
		freeHOSTNAME(pThis);
		if(pThis->pInputName != NULL)
			prop.Destruct(&pThis->pInputName);
		if((pThis->msgFlags & NEEDS_DNSRESOL) == 0) {
			if(pThis->rcvFrom.pRcvFrom != NULL)
				prop.Destruct(&pThis->rcvFrom.pRcvFrom);
		} else {
			free(pThis->rcvFrom.pfrominet);
		}
		if(pThis->pRcvFromIP != NULL)
			prop.Destruct(&pThis->pRcvFromIP);
		free(pThis->pszRcvdAt3164);
		free(pThis->pszRcvdAt3339);
		free(pThis->pszRcvdAt_MySQL);
		free(pThis->pszRcvdAt_PgSQL);
		free(pThis->pszTIMESTAMP_MySQL);
		free(pThis->pszTIMESTAMP_PgSQL);
		if(pThis->pCSProgName != NULL)
			rsCStrDestruct(&pThis->pCSProgName);
		if(pThis->pCSStrucData != NULL)
			rsCStrDestruct(&pThis->pCSStrucData);
		if(pThis->pCSAPPNAME != NULL)
			rsCStrDestruct(&pThis->pCSAPPNAME);
		if(pThis->pCSPROCID != NULL)
			rsCStrDestruct(&pThis->pCSPROCID);
		if(pThis->pCSMSGID != NULL)
			rsCStrDestruct(&pThis->pCSMSGID);
#	ifndef HAVE_ATOMIC_BUILTINS
		MsgUnlock(pThis);
# 	endif
		funcDeleteMutex(pThis);


#		if HAVE_MALLOC_TRIM
		{


			static unsigned iTrimCtr = 1;
			currCnt = ATOMIC_INC_AND_FETCH_unsigned(&iTrimCtr, &mutTrimCtr);
			if(currCnt % 100000 == 0) {
				malloc_trim(128*1024);
			}
		}
#		endif
	} else {
}
