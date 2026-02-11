deleteDicomDirBackup()
{

    if (OFStandard::fileExists(BackupFilename))
    {
        if (BackupCreated)
            DCMDATA_INFO("deleting DICOMDIR backup: " << BackupFilename);
        else
            DCMDATA_INFO("deleting old DICOMDIR backup: " << BackupFilename);

        unlink(BackupFilename.c_str());
    }

    BackupCreated = OFFalse;
}
