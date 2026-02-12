vncProperties::Save()
{
	HKEY appkey;
	DWORD dw;

	if (!m_allowproperties)
		return;


	if (m_usersettings) {

		char username[UNLEN+1];
		if (!vncService::CurrentUser((char *)&username, sizeof(username)))
			return;
		if (strcmp(username, "") == 0)
			return;


		if (RegCreateKeyEx(HKEY_CURRENT_USER,
			WINVNC_REGISTRY_KEY,
			0, REG_NONE, REG_OPTION_NON_VOLATILE,
			KEY_WRITE | KEY_READ, NULL, &appkey, &dw) != ERROR_SUCCESS)
			return;
	} else {

		HKEY hkLocal;
		if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,
			WINVNC_REGISTRY_KEY,
			0, REG_NONE, REG_OPTION_NON_VOLATILE,
			KEY_READ, NULL, &hkLocal, &dw) != ERROR_SUCCESS) {
			MessageBoxSecure(NULL, sz_ID_MB1, sz_ID_WVNC, MB_OK);
			return;
		}

		if (RegCreateKeyEx(hkLocal,
			"Default",
			0, REG_NONE, REG_OPTION_NON_VOLATILE,
			KEY_WRITE | KEY_READ, NULL, &appkey, &dw) != ERROR_SUCCESS) {
			RegCloseKey(hkLocal);
			return;
		}
		RegCloseKey(hkLocal);
	}


	SaveUserPrefs(appkey);
	RegCloseKey(appkey);
	RegCloseKey(HKEY_CURRENT_USER);


	HKEY hkLocal,hkDefault;
	if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		WINVNC_REGISTRY_KEY,
		0, REG_NONE, REG_OPTION_NON_VOLATILE,
		KEY_WRITE | KEY_READ, NULL, &hkLocal, &dw) != ERROR_SUCCESS)
		return;
	if (RegCreateKeyEx(hkLocal,
		"Default",
		0, REG_NONE, REG_OPTION_NON_VOLATILE,
		KEY_WRITE | KEY_READ,
		NULL,
		&hkDefault,
		&dw) != ERROR_SUCCESS)
		hkDefault = NULL;

	SaveInt(hkLocal, "DebugMode", vnclog.GetMode());
	SaveInt(hkLocal, "Avilog", vnclog.GetVideo());
	SaveString(hkLocal, "path", vnclog.GetPath());
	SaveInt(hkLocal, "DebugLevel", vnclog.GetLevel());
	SaveInt(hkLocal, "AllowLoopback", m_server->LoopbackOk());
#ifdef IPV6V4
	SaveInt(hkLocal, "UseIpv6", m_server->IPV6());
#endif
	SaveInt(hkLocal, "LoopbackOnly", m_server->LoopbackOnly());
	if (hkDefault)
		{
			SaveInt(hkDefault, "AllowShutdown", m_allowshutdown);
			SaveInt(hkDefault, "AllowProperties",  m_allowproperties);
			SaveInt(hkDefault, "AllowEditClients", m_alloweditclients);
		}

	SaveInt(hkLocal, "DisableTrayIcon", m_server->GetDisableTrayIcon());
	SaveInt(hkLocal, "rdpmode", m_server->GetRdpmode());
	SaveInt(hkLocal, "noscreensaver", m_server->GetNoScreensaver());
	SaveInt(hkLocal, "Secure", m_server->Secure());
	SaveInt(hkLocal, "MSLogonRequired", m_server->MSLogonRequired());

	SaveInt(hkLocal, "NewMSLogon", m_server->GetNewMSLogon());
	SaveInt(hkLocal, "ReverseAuthRequired", m_server->GetReverseAuthRequired());

	SaveInt(hkLocal, "UseDSMPlugin", m_server->IsDSMPluginEnabled());
	SaveInt(hkLocal, "ConnectPriority", m_server->ConnectPriority());
	SaveDSMPluginName(hkLocal, m_server->GetDSMPluginName());


	SaveString(hkLocal, "DSMPluginConfig", m_server->GetDSMPluginConfig());

	if (hkDefault) RegCloseKey(hkDefault);
	if (hkLocal) RegCloseKey(hkLocal);
}
