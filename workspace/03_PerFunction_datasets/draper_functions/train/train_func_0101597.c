updateNotify(callback *callbackArg)
{
	if (!smap && (!hasCapability("IDLE") || noIdle))
	{
		if (callbackArg)
			callbackArg->success("Ok");
		return;
	}

	installForegroundTask(smap ?
			      (imapHandler *)new smapIdleHandler(wantIdleMode,
								 callbackArg):
			      new imapIdleHandler(wantIdleMode, callbackArg));
}
