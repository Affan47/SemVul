vncProperties::SavePassword2(HKEY key, char *buffer)
{
	RegSetValueEx(key, "Password2", 0, REG_BINARY, (LPBYTE) buffer, MAXPWLEN);
}
