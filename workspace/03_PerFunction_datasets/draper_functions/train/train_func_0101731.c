URLNotify (const char *url,
		        NPReason reason,
		        void *notifyData)
{
	const char *reasons[] = {
		"Base (undefined)",
		"Done",
		"Network error",
		"User break"
	};
	D ("URLNotify URL '%s' reason %d (%s)", url ? url : "", reason, reasons[reason]);


	if (mExpectingStream) {
		if (reason == NPRES_NETWORK_ERR) {
			totem_dbus_proxy_call_no_reply (mViewerProxy,
							"SetErrorLogo",
							NULL);
		} else if (reason != NPRES_DONE) {
			Dm ("Failed to get stream");

		}

		mExpectingStream = false;
	}
}
