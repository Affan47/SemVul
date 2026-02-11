updateDicomDir(const E_ApplicationProfile profile,
                                              const char *filename)
{
    OFCondition result = EC_IllegalParameter;
    if (filename != NULL)
    {
        FilesetUpdateMode = OFTrue;

        cleanup();

        if (OFStandard::fileExists(filename))
        {

            if (BackupMode)
                createDicomDirBackup(filename);

            result = selectApplicationProfile(profile);
            if (result.good())
            {
                DCMDATA_INFO("updating DICOMDIR file using " << getProfileName(ApplicationProfile)
                    << " profile: " << filename);

                DicomDir = new DcmDicomDir(filename);
                if (DicomDir != NULL)
                    result = DicomDir->error();
                else
                    result = EC_MemoryExhausted;
            }
        } else {

            char buffer[255];
            const char *text = OFStandard::strerror(ENOENT, buffer, 255);
            if ((text == NULL) || (strlen(text) == 0))
                text = "(unknown error code)";

            result = makeOFCondition(OFM_dcmdata, 18, OF_error, text);

            DCMDATA_ERROR(result.text() << ": cannot update file: " << filename);
        }
    }
    return result;
}
