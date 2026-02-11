unzipAllFilesIntoDirs(const QStringList &paths)
{
    foreach(QString p, paths) {
        QDir d(p);
        if (!d.exists())
            continue;


        d.setNameFilters(QStringList() << "*.zip");
        d.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Readable);
        QStringList zipFiles = d.entryList();

        foreach(QString f, zipFiles) {

            QDir dz(p);
            dz.setFilter(QDir::Files | QDir::NoSymLinks | QDir::Readable | QDir::NoDotAndDotDot);
            if ((dz.cd(QFileInfo(f).baseName())) &&
                    (dz.entryList().count()))
                continue;


            if (!d.cd(QFileInfo(f).baseName() )) {
                d.mkdir(QFileInfo(f).baseName());
                dz.cd(QFileInfo(f).baseName());
            }
            else d.cdUp();


            unzipFile(d.absolutePath() + QDir::separator() + f, dz.absolutePath());
        }
    }
    return true;
}
