void vncProperties::ReloadDynamicSettings()
{
	char username[UNLEN+1];


	if (!vncService::CurrentUser((char *)&username, sizeof(username)))
	{
		vnclog.Print(LL_INTINFO, VNCLOG("***** DBG - NO current user\n"));
		return;
	}


	if (strcmp(username, "") == 0)
	{

		strcpy_s((char *)&username, UNLEN+1, "SYSTEM");
	}


	vnclog.SetMode(myIniFile.ReadInt("admin", "DebugMode", 0));
	vnclog.SetLevel(myIniFile.ReadInt("admin", "DebugLevel", 0));
}
