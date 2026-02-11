serverResponse(const char *message)
{
	const char *p=strchr(message, ' ');

	if (p)
		message=p+1;

	mail::callback *c=callbackPtr;

	callbackPtr=NULL;

	disconnectCallback=c;

	if (myserver->socketEndEncryption())
		return;

	myserver->socketDisconnect();
	myserver->orderlyShutdown=true;
	myserver->disconnect("");
}
