void ImportEPUB::LocateOrCreateNCX(const QString &ncx_id_on_spine)
{
    QString load_warning;
    QString ncx_href = "not_found";
    m_NCXId = ncx_id_on_spine;


    if (!m_NCXId.isEmpty()) {
        ncx_href = m_NcxCandidates[ m_NCXId ];
    } else {


        QHashIterator<QString, QString> ncxSearch(m_NcxCandidates);

        while (ncxSearch.hasNext()) {
            ncxSearch.next();

            if (QFileInfo(ncxSearch.value()).suffix().toLower() == NCX_EXTENSION) {
                m_NCXId = ncxSearch.key();
                load_warning = QObject::tr("The OPF file did not identify the NCX file correctly.") + "\n" +
                               " - "  +  QObject::tr("Sigil has used the following file as the NCX:") +
                               QString(" %1").arg(m_NcxCandidates[ m_NCXId ]);
                ncx_href = m_NcxCandidates[ m_NCXId ];
                break;
            }
        }
    }

    m_NCXFilePath = QFileInfo(m_OPFFilePath).absolutePath() % "/" % ncx_href;

    if (ncx_href.isEmpty() || !QFile::exists(m_NCXFilePath)) {
        m_NCXNotInManifest = m_NCXId.isEmpty() || ncx_href.isEmpty();
        m_NCXId.clear();


        m_NCXFilePath = QFileInfo(m_OPFFilePath).absolutePath() % "/" % NCX_FILE_NAME;

        NCXResource ncx_resource(m_ExtractedFolderPath, m_NCXFilePath, m_Book->GetFolderKeeper());


        if (!m_UuidIdentifierValue.isEmpty()) {
            ncx_resource.SetMainID(m_UuidIdentifierValue);
        }

        ncx_resource.SaveToDisk();

        if (m_PackageVersion.startsWith('3')) {
            load_warning = QObject::tr("Sigil has created a template NCX") + "\n" +
              QObject::tr("to support epub2 backwards compatibility.");
        } else {
            if (ncx_href.isEmpty()) {
                load_warning = QObject::tr("The OPF file does not contain an NCX file.") + "\n" +
                               " - " +  QObject::tr("Sigil has created a new one for you.");
            } else {
                load_warning = QObject::tr("The NCX file is not present in this EPUB.") + "\n" +
                               " - " + QObject::tr("Sigil has created a new one for you.");
            }
        }
    }

    if (!load_warning.isEmpty()) {
        AddLoadWarning(load_warning);
    }
}
