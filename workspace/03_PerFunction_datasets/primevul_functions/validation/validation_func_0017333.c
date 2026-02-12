int ntlm_read_version_info(wStream* s, NTLM_VERSION_INFO* versionInfo)
{
	if (Stream_GetRemainingLength(s) < 8)
		return -1;

	Stream_Read_UINT8(s, versionInfo->ProductMajorVersion);
	Stream_Read_UINT8(s, versionInfo->ProductMinorVersion);
	Stream_Read_UINT16(s, versionInfo->ProductBuild);
	Stream_Read(s, versionInfo->Reserved, sizeof(versionInfo->Reserved));
	Stream_Read_UINT8(s, versionInfo->NTLMRevisionCurrent);
	return 1;
}
