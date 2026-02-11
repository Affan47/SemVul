checkFile( const QString &checkFilename )
{
    const QFileInfo checkFile(checkFilename);
    if (!checkFile.exists())
    {
        return CheckFileDoesNotExist;
    }
    if (!checkFile.isFile())
    {
        return CheckFileIsNotFile;
    }
    if (!checkFile.isReadable())
    {
        return CheckFileIsNotReadable;
    }
    return CheckFileSuccess;
}
