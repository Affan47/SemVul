QSharedPointer<Book> ImportEPUB::GetBook(bool extract_metadata)
{
    QList<XMLResource *> non_well_formed;
    SettingsStore ss;

    if (!Utility::IsFileReadable(m_FullFilePath)) {
        throw (EPUBLoadParseError(QString(QObject::tr("Cannot read EPUB: %1")).arg(QDir::toNativeSeparators(m_FullFilePath)).toStdString()));
    }


    ExtractContainer();
    QHash<QString, QString> encrypted_files = ParseEncryptionXml();

    if (BookContentEncrypted(encrypted_files)) {
        throw (FileEncryptedWithDrm(""));
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);


    LocateOPF();
    m_opfDir = QFileInfo(m_OPFFilePath).dir();

    ReadOPF();
    AddObfuscatedButUndeclaredFonts(encrypted_files);
    AddNonStandardAppleXML();
    LoadInfrastructureFiles();

    QStringList notInManifest;
    foreach(QString file_path, m_ZipFilePaths) {

        if (file_path == "mimetype") continue;
        if (file_path.startsWith("META-INF")) continue;
	if (m_OPFFilePath.contains(file_path)) continue;
	if (!m_ManifestFilePaths.contains(file_path)) {
	    notInManifest << file_path;
	}
    }
    if (!notInManifest.isEmpty()) {
        Utility::DisplayStdWarningDialog(tr("Files exist in epub that are not listed in the manifest, they will be ignored"), notInManifest.join("\n"));
    }
    const QHash<QString, QString> updates = LoadFolderStructure();
    const QList<Resource *> resources     = m_Book->GetFolderKeeper()->GetResourceList();


    for (int i=0; i<resources.count(); ++i) {
        if (resources.at(i)->Type() == Resource::HTMLResourceType) {
            HTMLResource *hresource = dynamic_cast<HTMLResource *>(resources.at(i));
            if (!hresource) {
                continue;
            }

            try {
                hresource->SetText(HTMLEncodingResolver::ReadHTMLFile(hresource->GetFullPath()));
            } catch (...) {
                if (ss.cleanOn() & CLEANON_OPEN) {
                    non_well_formed << hresource;
                    continue;
                }
            }
            if (ss.cleanOn() & CLEANON_OPEN) {
              if (!XhtmlDoc::IsDataWellFormed(hresource->GetText(),hresource->GetEpubVersion())) {
                    non_well_formed << hresource;
                }
            }
        }
    }
    if (!non_well_formed.isEmpty()) {
        QApplication::restoreOverrideCursor();
        if (QMessageBox::Yes == QMessageBox::warning(QApplication::activeWindow(),
                tr("Sigil"),
                tr("This EPUB has HTML files that are not well formed. "
                   "Sigil can attempt to automatically fix these files, although this "
                   "can result in data loss.\n\n"
                   "Do you want to automatically fix the files?"),
                QMessageBox::Yes|QMessageBox::No)
           ) {
            non_well_formed.clear();
        }
        QApplication::setOverrideCursor(Qt::WaitCursor);
    }

    const QStringList load_errors = UniversalUpdates::PerformUniversalUpdates(false, resources, updates, non_well_formed);

    Q_FOREACH (QString err, load_errors) {
        AddLoadWarning(QString("%1").arg(err));
    }

    ProcessFontFiles(resources, updates, encrypted_files);

    if (m_PackageVersion.startsWith('3')) {
        HTMLResource * nav_resource = NULL;
        if (m_NavResource) {
            if (m_NavResource->Type() == Resource::HTMLResourceType) {
                nav_resource = dynamic_cast<HTMLResource*>(m_NavResource);
            }
        }
        if (!nav_resource) {


            nav_resource = m_Book->CreateEmptyNavFile(true);
            Resource * res = dynamic_cast<Resource *>(nav_resource);
            m_Book->GetOPF()->SetItemRefLinear(res, false);
        }
        m_Book->GetOPF()->SetNavResource(nav_resource);
    }

    if (m_NCXNotInManifest) {


        m_NCXId = m_Book->GetOPF()->AddNCXItem(m_NCXFilePath);
    }


    m_Book->GetOPF()->UpdateNCXOnSpine(m_NCXId);

    m_Book->GetOPF()->UpdateNCXLocationInManifest(m_Book->GetNCX());


    if (!m_HasSpineItems) {
        QList<MetaEntry> originalMetadata = m_Book->GetOPF()->GetDCMetadata();
        m_Book->GetOPF()->AutoFixWellFormedErrors();
        if (extract_metadata) {
            m_Book->GetOPF()->SetDCMetadata(originalMetadata);
        }
        AddLoadWarning(QObject::tr("The OPF file does not contain a valid spine.") % "\n" %
                       QObject::tr("Sigil has created a new one for you."));
    }


    m_Book->SetModified(GetLoadWarnings().count() > 0);
    QApplication::restoreOverrideCursor();
    return m_Book;
}
