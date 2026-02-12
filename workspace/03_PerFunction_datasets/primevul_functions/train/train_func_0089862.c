vncProperties::SaveUserPrefs(HKEY appkey)
{

	vnclog.Print(LL_INTINFO, VNCLOG("saving current settings to registry\n"));


	SaveInt(appkey, "FileTransferEnabled", m_server->FileTransferEnabled());
	SaveInt(appkey, "FTUserImpersonation", m_server->FTUserImpersonation());
	SaveInt(appkey, "BlankMonitorEnabled", m_server->BlankMonitorEnabled());
	SaveInt(appkey, "BlankInputsOnly", m_server->BlankInputsOnly());
	SaveInt(appkey, "primary", m_server->Primary());
	SaveInt(appkey, "secondary", m_server->Secondary());

	SaveInt(appkey, "DefaultScale", m_server->GetDefaultScale());

	SaveInt(appkey, "UseDSMPlugin", m_server->IsDSMPluginEnabled());
	SaveDSMPluginName(appkey, m_server->GetDSMPluginName());

	SaveString(appkey, "DSMPluginConfig", m_server->GetDSMPluginConfig());


	SaveInt(appkey, "SocketConnect", m_server->SockConnected());
	SaveInt(appkey, "HTTPConnect", m_server->HTTPConnectEnabled());
	SaveInt(appkey, "AutoPortSelect", m_server->AutoPortSelect());
	if (!m_server->AutoPortSelect()) {
		SaveInt(appkey, "PortNumber", m_server->GetPort());
		SaveInt(appkey, "HTTPPortNumber", m_server->GetHttpPort());
	}
	SaveInt(appkey, "InputsEnabled", m_server->RemoteInputsEnabled());
	SaveInt(appkey, "LocalInputsDisabled", m_server->LocalInputsDisabled());
	SaveInt(appkey, "IdleTimeout", m_server->AutoIdleDisconnectTimeout());
	SaveInt(appkey, "EnableJapInput", m_server->JapInputEnabled());
	SaveInt(appkey, "EnableUnicodeInput", m_server->UnicodeInputEnabled());
	SaveInt(appkey, "EnableWin8Helper", m_server->Win8HelperEnabled());


	SaveInt(appkey, "QuerySetting", m_server->QuerySetting());
	SaveInt(appkey, "QueryTimeout", m_server->QueryTimeout());
	SaveInt(appkey, "QueryDisableTime", m_server->QueryDisableTime());
	SaveInt(appkey, "QueryAccept", m_server->QueryAcceptForSave());
	SaveInt(appkey, "MaxViewerSetting", m_server->getMaxViewerSetting());
	SaveInt(appkey, "MaxViewers", m_server->getMaxViewers());
	SaveInt(appkey, "Collabo", m_server->getCollabo());
	SaveInt(appkey, "Frame", m_server->getFrame());
	SaveInt(appkey, "Notification", m_server->getNotification());
	SaveInt(appkey, "OSD", m_server->getOSD());
	SaveInt(appkey, "NotificationSelection", m_server->getNotificationSelection());


	SaveInt(appkey, "LockSetting", m_server->LockSettings());


	SaveInt(appkey, "RemoveWallpaper", m_server->RemoveWallpaperEnabled());


	SaveInt(appkey, "RemoveEffects", m_server->RemoveEffectsEnabled());
	SaveInt(appkey, "RemoveFontSmoothing", m_server->RemoveFontSmoothingEnabled());


	char passwd[MAXPWLEN];
	m_server->GetPassword(passwd);
	SavePassword(appkey, passwd);
	memset(passwd, '\0', MAXPWLEN);
	m_server->GetPassword2(passwd);
	SavePassword2(appkey, passwd);
}
