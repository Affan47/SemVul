SetSendSuffix(const char *suffix)
{
	if (sendSuffix)
	{
		rakFree_Ex(sendSuffix, _FILE_AND_LINE_ );
		sendSuffix=0;
	}
	if (suffix)
	{
		sendSuffix = (char*) rakMalloc_Ex(strlen(suffix)+1, _FILE_AND_LINE_);
		strcpy(sendSuffix, suffix);
	}
}
