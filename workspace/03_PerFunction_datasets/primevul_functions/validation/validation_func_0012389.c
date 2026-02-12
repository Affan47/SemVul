RateLimiter(qqueue_t *pThis)
{
	DEFiRet;
	int iDelay;
	int iHrCurr;
	time_t tCurr;
	struct tm m;

	ISOBJ_TYPE_assert(pThis, qqueue);

	iDelay = 0;
	if(pThis->iDeqtWinToHr != 25) {

		datetime.GetTime(&tCurr);
		localtime_r(&tCurr, &m);
		iHrCurr = m.tm_hour;

		if(pThis->iDeqtWinToHr < pThis->iDeqtWinFromHr) {
			if(iHrCurr < pThis->iDeqtWinToHr || iHrCurr > pThis->iDeqtWinFromHr) {
				;
			} else {
				iDelay = (pThis->iDeqtWinFromHr - iHrCurr) * 3600;


				iDelay -= m.tm_min * 60;
				iDelay -= m.tm_sec;
			}
		} else {
			if(iHrCurr >= pThis->iDeqtWinFromHr && iHrCurr < pThis->iDeqtWinToHr) {
				;
			} else {
				if(iHrCurr < pThis->iDeqtWinFromHr) {
					iDelay = (pThis->iDeqtWinFromHr - iHrCurr - 1) * 3600;
					iDelay += (60 - m.tm_min) * 60;
					iDelay += 60 - m.tm_sec;
				} else {
					iDelay = (24 - iHrCurr + pThis->iDeqtWinFromHr) * 3600;


					iDelay -= m.tm_min * 60;
					iDelay -= m.tm_sec;
				}
			}
		}
	}

	if(iDelay > 0) {
		DBGOPRINT((obj_t*) pThis, "outside dequeue time window, delaying %d seconds\n", iDelay);
		srSleep(iDelay, 0);
	}

	RETiRet;
}
