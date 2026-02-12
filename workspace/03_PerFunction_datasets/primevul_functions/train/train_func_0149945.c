mainloop(void)
{
	struct timeval tvSelectTimeout;

	BEGINfunc


	processImInternal();

	while(!bFinished){


		tvSelectTimeout.tv_sec = (bReduceRepeatMsgs == 1) ? TIMERINTVL : 86400 ;

		tvSelectTimeout.tv_usec = 0;
		select(1, NULL, NULL, NULL, &tvSelectTimeout);
		if(bFinished)
			break;


		if(bReduceRepeatMsgs == 1)
			doFlushRptdMsgs();

		if(bHadHUP) {
			doHUP();
			bHadHUP = 0;
			continue;
		}

	}
	ENDfunc
}
