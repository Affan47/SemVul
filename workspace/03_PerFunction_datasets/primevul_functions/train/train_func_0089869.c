vncProperties::Init(vncServer *server)
{

	m_server = server;


	m_fUseRegistry = ((myIniFile.ReadInt("admin", "UseRegistry", 0) == 1) ? TRUE : FALSE);


	if (m_fUseRegistry)
		Load(TRUE);
	else
		LoadFromIniFile();


	char passwd[MAXPWLEN];
	m_server->GetPassword(passwd);
	{
	    vncPasswd::ToText plain(passwd, m_pref_Secure);
	    if (strlen(plain) == 0)
			 if (!m_allowproperties || !RunningAsAdministrator ()) {
				if(m_server->AuthRequired()) {
					MessageBoxSecure(NULL, sz_ID_NO_PASSWD_NO_OVERRIDE_ERR,
								sz_ID_WINVNC_ERROR,
								MB_OK | MB_ICONSTOP);
					PostQuitMessage(0);
				}


			} else {

				if (m_server->AuthRequired()) {
					char username[UNLEN+1];
					if (!vncService::CurrentUser(username, sizeof(username)))
						return FALSE;
					if (strcmp(username, "") == 0) {
						Lock_service_helper=true;
						MessageBoxSecure(NULL, sz_ID_NO_PASSWD_NO_LOGON_WARN,
									sz_ID_WINVNC_ERROR,
									MB_OK | MB_ICONEXCLAMATION);
						ShowAdmin(TRUE, FALSE);
						Lock_service_helper=false;
					} else {
						ShowAdmin(TRUE, TRUE);
					}
				}
			}
	}
	Lock_service_helper=false;
	return TRUE;
}
