void ntlm_write_version_info(wStream* s, NTLM_VERSION_INFO* versionInfo)
{
	Stream_Write_UINT8(s, versionInfo->ProductMajorVersion);
	Stream_Write_UINT8(s, versionInfo->ProductMinorVersion);
	Stream_Write_UINT16(s, versionInfo->ProductBuild);
	Stream_Write(s, versionInfo->Reserved, sizeof(versionInfo->Reserved));
	Stream_Write_UINT8(s, versionInfo->NTLMRevisionCurrent);
}
