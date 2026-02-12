vncProperties::ShowAdmin(BOOL show, BOOL usersettings)
{

	HANDLE hProcess=NULL;
	HANDLE hPToken=NULL;
	DWORD id = vncService::GetExplorerLogonPid();
	int iImpersonateResult=0;
	{
		char WORKDIR[MAX_PATH];
		if (!GetTempPath(MAX_PATH,WORKDIR))
			{

				if (GetModuleFileName(NULL, WORKDIR, MAX_PATH))
				{
					char* p = strrchr(WORKDIR, '\\');
					if (p == NULL) return;
					*p = '\0';
				}
					strcpy_s(m_Tempfile,"");
					strcat_s(m_Tempfile,WORKDIR);
					strcat_s(m_Tempfile,"\\");
					strcat_s(m_Tempfile,INIFILE_NAME);
		}
		else
		{
			strcpy_s(m_Tempfile,"");
			strcat_s(m_Tempfile,WORKDIR);
			strcat_s(m_Tempfile,INIFILE_NAME);
		}
	}
	if (id!=0 && usersettings)
			{
				hProcess = OpenProcess(MAXIMUM_ALLOWED,FALSE,id);
				if(OpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY
										|TOKEN_DUPLICATE|TOKEN_ASSIGN_PRIMARY|TOKEN_ADJUST_SESSIONID
										|TOKEN_READ|TOKEN_WRITE,&hPToken))
				{
					ImpersonateLoggedOnUser(hPToken);
					iImpersonateResult = GetLastError();
					if(iImpersonateResult == ERROR_SUCCESS)
					{
						ExpandEnvironmentStringsForUser(hPToken, "%TEMP%", m_Tempfile, MAX_PATH);
						strcat_s(m_Tempfile,"\\");
						strcat_s(m_Tempfile,INIFILE_NAME);
					}
				}
	}

	if (!m_allowproperties)
	{
		if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
		if (hProcess) CloseHandle(hProcess);
		if (hPToken) CloseHandle(hPToken);
		return;
	}


	if (m_fUseRegistry)
	{
		if (vncService::RunningAsService()) usersettings=false;
		m_usersettings=usersettings;
	}

	if (show)
	{

		if (!m_fUseRegistry)
		{


		}
		else
		{

			if (usersettings)
			{
				char username[UNLEN+1];
				if (!vncService::CurrentUser(username, sizeof(username)))
					{
						if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
						CloseHandle(hProcess);
						CloseHandle(hPToken);
						return;
					}
				if (strcmp(username, "") == 0) {
					MessageBoxSecure(NULL, sz_ID_NO_CURRENT_USER_ERR, sz_ID_WINVNC_ERROR, MB_OK | MB_ICONEXCLAMATION);
					if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
					CloseHandle(hProcess);
					CloseHandle(hPToken);
					return;
				}
			}
			else
			{

				HKEY hkLocal=NULL;
				HKEY hkDefault=NULL;
				BOOL canEditDefaultPrefs = 1;
				DWORD dw;
				if (RegCreateKeyEx(HKEY_LOCAL_MACHINE,
					WINVNC_REGISTRY_KEY,
					0, REG_NONE, REG_OPTION_NON_VOLATILE,
					KEY_READ, NULL, &hkLocal, &dw) != ERROR_SUCCESS)
					canEditDefaultPrefs = 0;
				else if (RegCreateKeyEx(hkLocal,
					"Default",
					0, REG_NONE, REG_OPTION_NON_VOLATILE,
					KEY_WRITE | KEY_READ, NULL, &hkDefault, &dw) != ERROR_SUCCESS)
					canEditDefaultPrefs = 0;
				if (hkLocal) RegCloseKey(hkLocal);
				if (hkDefault) RegCloseKey(hkDefault);

				if (!canEditDefaultPrefs) {
					MessageBoxSecure(NULL, sz_ID_CANNOT_EDIT_DEFAULT_PREFS, sz_ID_WINVNC_ERROR, MB_OK | MB_ICONEXCLAMATION);
					if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
					if (hProcess) CloseHandle(hProcess);
					if (hPToken) CloseHandle(hPToken);
					return;
				}
			}
		}


		if (!m_dlgvisible)
		{
			if (m_fUseRegistry)
			{
				if (usersettings)
					vnclog.Print(LL_INTINFO, VNCLOG("show per-user Properties\n"));
				else
					vnclog.Print(LL_INTINFO, VNCLOG("show default system Properties\n"));


				m_usersettings=usersettings;
			}

			for (;;)
			{
				m_returncode_valid = FALSE;


				m_bExpanded = true;
				cy = 0;
				cx = 0;
				int result = (int)DialogBoxParam(hInstResDLL,
				    MAKEINTRESOURCE(IDD_PROPERTIES1),
				    NULL,
				    (DLGPROC) DialogProc,
				    (LONG_PTR) this);

				if (!m_returncode_valid)
				    result = IDCANCEL;

				vnclog.Print(LL_INTINFO, VNCLOG("dialog result = %d\n"), result);

				if (result == -1)
				{

					PostQuitMessage(0);
					if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
					CloseHandle(hProcess);
					CloseHandle(hPToken);
					return;
				}


				char passwd[MAXPWLEN];
				m_server->GetPassword(passwd);
				{
				    vncPasswd::ToText plain(passwd, m_server->Secure());
				    if ((strlen(plain) != 0) || !m_server->AuthRequired())
					break;
				}

				vnclog.Print(LL_INTERR, VNCLOG("warning - empty password\n"));


				int result2 = MessageBoxSecure(NULL, sz_ID_NO_PASSWORD_WARN,
					sz_ID_WINVNC_WARNIN, MB_OK | MB_ICONEXCLAMATION);


				if (result == IDCANCEL)
				{
				    vnclog.Print(LL_INTERR, VNCLOG("no password - QUITTING\n"));
				    PostQuitMessage(0);
				    if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
					CloseHandle(hProcess);
					CloseHandle(hPToken);
					fShutdownOrdered = true;
					return;
				}

				omni_thread::sleep(4);
			}


			if (!vncService::RunningAsService())
			{
			if (m_fUseRegistry)
				Load(TRUE);
			else
				LoadFromIniFile();
			}

		}
	}
	if(iImpersonateResult == ERROR_SUCCESS)RevertToSelf();
	if (hProcess) CloseHandle(hProcess);
	if (hPToken) CloseHandle(hPToken);
}
