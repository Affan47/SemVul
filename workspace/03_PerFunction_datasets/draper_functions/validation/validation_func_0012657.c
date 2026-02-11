Create( const char * pszName,
                                        char **papszOptions )
{
    OGRSFDriver* poGPXDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName("GPX");
    if (poGPXDriver == NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined, "GPX driver is necessary for GPSBabel write support");
        return FALSE;
    }

    if (!EQUALN(pszName, "GPSBABEL:", 9))
    {
        const char* pszOptionGPSBabelDriverName =
                CSLFetchNameValue(papszOptions, "GPSBABEL_DRIVER");
        if (pszOptionGPSBabelDriverName != NULL)
            pszGPSBabelDriverName = CPLStrdup(pszOptionGPSBabelDriverName);
        else
        {
            CPLError(CE_Failure, CPLE_AppDefined, "GPSBABEL_DRIVER dataset creation option expected");
            return FALSE;
        }

        pszFilename = CPLStrdup(pszName);
    }
    else
    {
        const char* pszSep = strchr(pszName + 9, ':');
        if (pszSep == NULL)
        {
            CPLError(CE_Failure, CPLE_AppDefined,
                    "Wrong syntax. Expected GPSBabel:driver_name[,options]*:file_name");
            return FALSE;
        }

        pszGPSBabelDriverName = CPLStrdup(pszName + 9);
        *(strchr(pszGPSBabelDriverName, ':')) = '\0';

        pszFilename = CPLStrdup(pszSep+1);
    }


    if (!OGRGPSBabelDataSource::IsValidDriverName(pszGPSBabelDriverName))
        return FALSE;

    const char* pszOptionUseTempFile = CSLFetchNameValue(papszOptions, "USE_TEMPFILE");
    if (pszOptionUseTempFile == NULL)
        pszOptionUseTempFile = CPLGetConfigOption("USE_TEMPFILE", NULL);
    if (pszOptionUseTempFile && CSLTestBoolean(pszOptionUseTempFile))
        osTmpFileName = CPLGenerateTempFilename(NULL);
    else
        osTmpFileName.Printf("/vsimem/ogrgpsbabeldatasource_%p", this);

    poGPXDS = poGPXDriver->CreateDataSource(osTmpFileName.c_str(), papszOptions);
    if (poGPXDS == NULL)
        return FALSE;

    this->pszName = CPLStrdup(pszName);

    return TRUE;
}
