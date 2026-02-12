LONG ValidateSignature(HWND hDlg, const char* path)
{
	LONG r = TRUST_E_SYSTEM_ERROR;
	WINTRUST_DATA trust_data = { 0 };
	WINTRUST_FILE_INFO trust_file = { 0 };
	PF_TYPE_DECL(WINAPI, long, WinVerifyTrustEx, (HWND, GUID*, WINTRUST_DATA*));
	PF_INIT(WinVerifyTrustEx, WinTrust);
	GUID guid_generic_verify =
		{ 0xaac56b, 0xcd44, 0x11d0,{ 0x8c, 0xc2, 0x0, 0xc0, 0x4f, 0xc2, 0x95, 0xee } };
	char *signature_name;
	size_t i;
	uint64_t current_ts, update_ts;


	signature_name = GetSignatureName(path, cert_country, (hDlg == INVALID_HANDLE_VALUE));
	if (signature_name == NULL) {
		uprintf("PKI: Could not get signature name");
		if (hDlg != INVALID_HANDLE_VALUE)
			MessageBoxExU(hDlg, lmprintf(MSG_284), lmprintf(MSG_283), MB_OK | MB_ICONERROR | MB_IS_RTL, selected_langid);
		return TRUST_E_NOSIGNATURE;
	}
	for (i = 0; i < ARRAYSIZE(cert_name); i++) {
		if (strcmp(signature_name, cert_name[i]) == 0)
			break;
	}
	if (i >= ARRAYSIZE(cert_name)) {
		uprintf("PKI: Signature '%s' is unexpected...", signature_name);
		if ((hDlg == INVALID_HANDLE_VALUE) || (MessageBoxExU(hDlg,
			lmprintf(MSG_285, signature_name), lmprintf(MSG_283),
			MB_YESNO | MB_ICONWARNING | MB_IS_RTL, selected_langid) != IDYES))
			return TRUST_E_EXPLICIT_DISTRUST;
	}

	trust_file.cbStruct = sizeof(trust_file);
	trust_file.pcwszFilePath = utf8_to_wchar(path);
	if (trust_file.pcwszFilePath == NULL) {
		uprintf("PKI: Unable to convert '%s' to UTF16", path);
		return ERROR_SEVERITY_ERROR | FAC(FACILITY_CERT) | ERROR_NOT_ENOUGH_MEMORY;
	}

	trust_data.cbStruct = sizeof(trust_data);


	trust_data.dwUIChoice = WTD_UI_NONE;

	trust_data.fdwRevocationChecks = WTD_REVOKE_WHOLECHAIN;

	trust_data.dwProvFlags = WTD_REVOCATION_CHECK_CHAIN | 0x400;
	trust_data.dwUnionChoice = WTD_CHOICE_FILE;
	trust_data.pFile = &trust_file;

	if (pfWinVerifyTrustEx != NULL)
		r = pfWinVerifyTrustEx(INVALID_HANDLE_VALUE, &guid_generic_verify, &trust_data);
	safe_free(trust_file.pcwszFilePath);
	switch (r) {
	case ERROR_SUCCESS:

		if (hDlg == INVALID_HANDLE_VALUE)
			break;


		current_ts = GetSignatureTimeStamp(NULL);
		if (current_ts == 0ULL) {
			uprintf("PKI: Cannot retrieve the current binary's timestamp - Aborting update");
			r = TRUST_E_TIME_STAMP;
		} else {
			update_ts = GetSignatureTimeStamp(path);
			if (update_ts < current_ts) {
				uprintf("PKI: Update timestamp (%" PRIi64 ") is younger than ours (%" PRIi64 ") - Aborting update", update_ts, current_ts);
				r = TRUST_E_TIME_STAMP;
			}
		}
		if ((r != ERROR_SUCCESS) && (force_update < 2))
			MessageBoxExU(hDlg, lmprintf(MSG_300), lmprintf(MSG_299), MB_OK | MB_ICONERROR | MB_IS_RTL, selected_langid);
		break;
	case TRUST_E_NOSIGNATURE:

		uprintf("PKI: File does not appear to be signed: %s", WinPKIErrorString());
		if (hDlg != INVALID_HANDLE_VALUE)
			MessageBoxExU(hDlg, lmprintf(MSG_284), lmprintf(MSG_283), MB_OK | MB_ICONERROR | MB_IS_RTL, selected_langid);
		break;
	default:
		uprintf("PKI: Failed to validate signature: %s", WinPKIErrorString());
		if (hDlg != INVALID_HANDLE_VALUE)
			MessageBoxExU(hDlg, lmprintf(MSG_240), lmprintf(MSG_283), MB_OK | MB_ICONERROR | MB_IS_RTL, selected_langid);
		break;
	}

	return r;
}
