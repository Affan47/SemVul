BOOL license_generate_hwid(rdpLicense* license)
{
	const BYTE* hashTarget;
	size_t targetLen;
	BYTE macAddress[6];

	ZeroMemory(license->HardwareId, HWID_LENGTH);

	if (license->rdp->settings->OldLicenseBehaviour)
	{
		ZeroMemory(macAddress, sizeof(macAddress));
		hashTarget = macAddress;
		targetLen = sizeof(macAddress);
	}
	else
	{
		wStream s;
		const char* hostname = license->rdp->settings->ClientHostname;
		Stream_StaticInit(&s, license->HardwareId, 4);
		Stream_Write_UINT32(&s, PLATFORMID);
		Stream_Free(&s, TRUE);

		hashTarget = (const BYTE*)hostname;
		targetLen = strlen(hostname);
	}


	return winpr_Digest_Allow_FIPS(WINPR_MD_MD5, hashTarget, targetLen,
	                               &license->HardwareId[HWID_PLATFORM_ID_LENGTH],
	                               WINPR_MD5_DIGEST_LENGTH);
}
