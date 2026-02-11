expImpInit(
	IF_FileHdl *		pFileHdl,
	FLMUINT				uiFlag,
	EXP_IMP_INFO *		pExpImpInfoRV)
{
	RCODE 				rc = FERR_OK;

	f_memset( pExpImpInfoRV, 0, sizeof(EXP_IMP_INFO));
	pExpImpInfoRV->pFileHdl = pFileHdl;
	pExpImpInfoRV->bDictRecords = (uiFlag == EXPIMP_IMPORT_EXPORT_GEDCOM)
														? FALSE
														: TRUE;


	pExpImpInfoRV->uiBufSize = (uiFlag == EXPIMP_IMPORT_EXPORT_GEDCOM)
												? (FLMUINT) 2048
												: (FLMUINT) 32768;
	for (;;)
	{
		if (RC_BAD( rc = f_alloc( pExpImpInfoRV->uiBufSize, &pExpImpInfoRV->pBuf)))
		{
			pExpImpInfoRV->uiBufSize -= 512;
			if (pExpImpInfoRV->uiBufSize < 1024)
			{
				pExpImpInfoRV->uiBufSize = 0;
				goto Exit;
			}
		}
		else
		{
			break;
		}
	}


	if (uiFlag == EXPIMP_EXPORT_DICTIONARY)
	{


		rc = expWrite( pExpImpInfoRV, FlmBinaryGedHeader, BINARY_GED_HEADER_LEN);
	}
	else if (uiFlag == EXPIMP_IMPORT_DICTIONARY)
	{
		rc = pFileHdl->seek( (FLMUINT) BINARY_GED_HEADER_LEN, FLM_IO_SEEK_SET,
								  &pExpImpInfoRV->ui64FilePos);
	}
	else
	{
		rc = expWrite( pExpImpInfoRV, FlmBinaryRecHeader, BINARY_GED_HEADER_LEN);
	}

Exit:

	if (RC_BAD( rc))
	{
		expImpFree( pExpImpInfoRV);
	}

	return (rc);
}
