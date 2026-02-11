doJtagCommand(uchar *command, int  commandSize, int  responseSize)
{
    int tryCount = 0;


    for (;;)
    {
	uchar *response;
	static uchar sync[] = { ' ' };
	static uchar stop[] = { 'S', JTAG_EOM };

	switch (sendJtagCommand(command, commandSize, &tryCount))
	{
	case send_ok:
	    response = getJtagResponse(responseSize);
	    check(response != NULL, JTAG_CAUSE);
	    return response;
	case send_failed:

	    while (sendJtagCommand(sync, sizeof sync, &tryCount) != send_ok)
		;
	    break;
	default:


	    if (sendJtagCommand(stop, sizeof stop, &tryCount) == send_ok)
		getJtagResponse(8);
	    break;
	}
    }

}
