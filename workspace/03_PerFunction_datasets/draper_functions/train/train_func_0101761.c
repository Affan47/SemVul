compressFile(QString fileCompressed, QString file)
{

    QuaZip zip(fileCompressed);
    QDir().mkpath(QFileInfo(fileCompressed).absolutePath());
    if(!zip.open(QuaZip::mdCreate))
    {
        QFile::remove(fileCompressed);
        return false;
    }


    if(!compressFile(&zip, file, QFileInfo(file).fileName()))
    {
        QFile::remove(fileCompressed);
        return false;
    }


    zip.close();
    if(zip.getZipError() != 0)
    {
        QFile::remove(fileCompressed);
        return false;
    }

    return true;
}
