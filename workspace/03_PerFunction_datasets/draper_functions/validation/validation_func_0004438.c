Open( const char *pszFilename,
                                                 const char *pszAccess)
{
    char* zipFilename;
    CPLString osZipInFileName;

    if (strchr(pszAccess, 'w') != NULL)
    {
        return OpenForWrite(pszFilename, pszAccess);
    }

    if (strchr(pszAccess, '+') != NULL)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Random access not supported for /vsizip");
        return NULL;
    }

    zipFilename = SplitFilename(pszFilename, osZipInFileName, TRUE);
    if (zipFilename == NULL)
        return NULL;

    {
        CPLMutexHolder oHolder(&hMutex);
        if (oMapZipWriteHandles.find(zipFilename) != oMapZipWriteHandles.end() )
        {
            CPLError(CE_Failure, CPLE_AppDefined,
                    "Cannot read a zip file being written");
            CPLFree(zipFilename);
            return NULL;
        }
    }

    VSIArchiveReader* poReader = OpenArchiveFile(zipFilename, osZipInFileName);
    if (poReader == NULL)
    {
        CPLFree(zipFilename);
        return NULL;
    }

    VSIFilesystemHandler *poFSHandler =
        VSIFileManager::GetHandler( zipFilename);

    VSIVirtualHandle* poVirtualHandle =
        poFSHandler->Open( zipFilename, "rb" );

    CPLFree(zipFilename);
    zipFilename = NULL;

    if (poVirtualHandle == NULL)
    {
        delete poReader;
        return NULL;
    }

    unzFile unzF = ((VSIZipReader*)poReader)->GetUnzFileHandle();

    cpl_unzOpenCurrentFile(unzF);

    uLong64 pos = cpl_unzGetCurrentFileZStreamPos(unzF);

    unz_file_info file_info;
    cpl_unzGetCurrentFileInfo (unzF, &file_info, NULL, 0, NULL, 0, NULL, 0);

    cpl_unzCloseCurrentFile(unzF);

    delete poReader;

    VSIGZipHandle* poGZIPHandle = new VSIGZipHandle(poVirtualHandle,
                             NULL,
                             pos,
                             file_info.compressed_size,
                             file_info.uncompressed_size,
                             file_info.crc,
                             file_info.compression_method == 0);


    return VSICreateBufferedReaderHandle(poGZIPHandle);
}
