downloadNext()
{
    mnCurrentDownload++;
    CComponentInfo& current = *mVecDownloads.at(mnCurrentDownload);

    QString sExt = current.GetURLFileExt();
    QString sFile = current.GetURLFilename();
    QString sInstallPath = current.GetInstallPath();
    QString sTempPath = QDir::tempPath() + "/";
    QString sDownloadPath;

    if (sExt == "exe")
    {
        sDownloadPath = sTempPath + sFile;
    }
    else if (sExt == "bz2")
    {
        sDownloadPath = sTempPath + sFile;
    }
    else if (sExt == "dll")
    {
        sDownloadPath = sInstallPath + sFile;
    }
    else
    {
        LOG(1, "Download '" << sFile << "' with ext: " << sExt << " not allowed" << "\n");
        Q_ASSERT(false);
        return;
    }

    LOG(3, "Will download " << current.GetDownloadURL() << " to '" <<
        sDownloadPath << "'\n");

    emit newFile(tr("Downloading %1").arg(current.GetURLFilename()));

    mFile.setFileName(sDownloadPath);
    if (!mFile.open(QIODevice::WriteOnly))
    {

        QString msg = QString("Couldn't open file '%1' for writing.").arg(mFile.fileName());
        LOG(1, msg << "\n");

        mFile.close();
        emit updateDownloadDone(true, msg);
        return;
    }

    QUrl url(current.GetDownloadURL());

    mTransport = new CachedHttp(this);
    mTransport->setHost(url.host());

    connect(mTransport, SIGNAL(requestFinished(int, bool)),
            this,       SLOT  (downloadDone(int, bool)), Qt::QueuedConnection);
    connect(mTransport, SIGNAL(dataReadProgress(int, int)),
            this,       SLOT  (httpProgressMade(int, int)));
    connect(mTransport, SIGNAL(stateChanged(int)),
            this,       SLOT  (statusChanged(int)));

    mHttpId = mTransport->get( url.path(), &mFile );

    mCancelled = false;
}
