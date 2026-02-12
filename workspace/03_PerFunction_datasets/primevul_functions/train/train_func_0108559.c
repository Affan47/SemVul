bool LibarchivePlugin::extractFiles(const QVector<Archive::Entry*> &files, const QString &destinationDirectory, const ExtractionOptions &options)
{
    if (!initializeReader()) {
        return false;
    }

    ArchiveWrite writer(archive_write_disk_new());
    if (!writer.data()) {
        return false;
    }

    archive_write_disk_set_options(writer.data(), extractionFlags());

    int totalEntriesCount = 0;
    const bool extractAll = files.isEmpty();
    if (extractAll) {
        if (!m_cachedArchiveEntryCount) {
            emit progress(0);


            qCDebug(ARK) << "For getting progress information, the archive will be listed once";
            m_emitNoEntries = true;
            list();
            m_emitNoEntries = false;
        }
        totalEntriesCount = m_cachedArchiveEntryCount;
    } else {
        totalEntriesCount = files.size();
    }

    qCDebug(ARK) << "Going to extract" << totalEntriesCount << "entries";

    qCDebug(ARK) << "Changing current directory to " << destinationDirectory;
    m_oldWorkingDir = QDir::currentPath();
    QDir::setCurrent(destinationDirectory);


    const bool preservePaths = options.preservePaths();
    const bool removeRootNode = options.isDragAndDropEnabled();
    bool overwriteAll = false;
    bool skipAll = false;
    bool dontPromptErrors = false;
    m_currentExtractedFilesSize = 0;
    int extractedEntriesCount = 0;
    int progressEntryCount = 0;
    struct archive_entry *entry;
    QString fileBeingRenamed;


    const QStringList fullPaths = entryFullPaths(files);
    QStringList remainingFiles = entryFullPaths(files);


    while (!QThread::currentThread()->isInterruptionRequested() && (archive_read_next_header(m_archiveReader.data(), &entry) == ARCHIVE_OK)) {

        if (!extractAll && remainingFiles.isEmpty()) {
            break;
        }

        fileBeingRenamed.clear();
        int index = -1;


    retry:
        const bool entryIsDir = S_ISDIR(archive_entry_mode(entry));

        if (!preservePaths && entryIsDir) {
            archive_read_data_skip(m_archiveReader.data());
            continue;
        }


        QString entryName = QDir::fromNativeSeparators(QFile::decodeName(archive_entry_pathname(entry)));


        if (entryName.startsWith(QLatin1String("./"))) {
            entryName.remove(0, 2);
        }


        if (entryName == QLatin1String("/") || entryName == QLatin1String("//")) {
            archive_read_data_skip(m_archiveReader.data());
            continue;
        }


        if (entryName.startsWith(QLatin1Char( '/' ))) {
            emit error(i18n("This archive contains archive entries with absolute paths, "
                            "which are not supported by Ark."));
            return false;
        }


        if (extractAll ||
            remainingFiles.contains(entryName) ||
            entryName == fileBeingRenamed) {


            if (entryName != fileBeingRenamed) {
                index = fullPaths.indexOf(entryName);
            }
            if (!extractAll && index == -1) {

                continue;
            }


            QFileInfo entryFI(entryName);


            const QString fileWithoutPath(entryFI.fileName());


            if (!preservePaths) {


                Q_ASSERT(!fileWithoutPath.isEmpty());
                archive_entry_copy_pathname(entry, QFile::encodeName(fileWithoutPath).constData());
                entryFI = QFileInfo(fileWithoutPath);


            } else if (!extractAll && removeRootNode && entryName != fileBeingRenamed) {
                const QString &rootNode = files.at(index)->rootNode;
                if (!rootNode.isEmpty()) {
                    const QString truncatedFilename(entryName.remove(entryName.indexOf(rootNode), rootNode.size()));
                    archive_entry_copy_pathname(entry, QFile::encodeName(truncatedFilename).constData());
                    entryFI = QFileInfo(truncatedFilename);
                }
            }


            if (!entryIsDir && entryFI.exists()) {
                if (skipAll) {
                    archive_read_data_skip(m_archiveReader.data());
                    archive_entry_clear(entry);
                    continue;
                } else if (!overwriteAll && !skipAll) {
                    Kerfuffle::OverwriteQuery query(entryName);
                    emit userQuery(&query);
                    query.waitForResponse();

                    if (query.responseCancelled()) {
                        emit cancelled();
                        archive_read_data_skip(m_archiveReader.data());
                        archive_entry_clear(entry);
                        break;
                    } else if (query.responseSkip()) {
                        archive_read_data_skip(m_archiveReader.data());
                        archive_entry_clear(entry);
                        continue;
                    } else if (query.responseAutoSkip()) {
                        archive_read_data_skip(m_archiveReader.data());
                        archive_entry_clear(entry);
                        skipAll = true;
                        continue;
                    } else if (query.responseRename()) {
                        const QString newName(query.newFilename());
                        fileBeingRenamed = newName;
                        archive_entry_copy_pathname(entry, QFile::encodeName(newName).constData());
                        goto retry;
                    } else if (query.responseOverwriteAll()) {
                        overwriteAll = true;
                    }
                }
            }


            if (entryIsDir && entryFI.exists()) {
                if (entryFI.isWritable()) {
                    qCWarning(ARK) << "Warning, existing, but writable dir";
                } else {
                    qCWarning(ARK) << "Warning, existing, but non-writable dir. skipping";
                    archive_entry_clear(entry);
                    archive_read_data_skip(m_archiveReader.data());
                    continue;
                }
            }


            const int returnCode = archive_write_header(writer.data(), entry);
            switch (returnCode) {
            case ARCHIVE_OK:


                copyData(entryName, m_archiveReader.data(), writer.data(), (extractAll && m_extractedFilesSize));
                break;

            case ARCHIVE_FAILED:
                qCCritical(ARK) << "archive_write_header() has returned" << returnCode
                                << "with errno" << archive_errno(writer.data());


                if (!dontPromptErrors) {

                    Kerfuffle::ContinueExtractionQuery query(QLatin1String(archive_error_string(writer.data())),
                                                             entryName);
                    emit userQuery(&query);
                    query.waitForResponse();

                    if (query.responseCancelled()) {
                        emit cancelled();
                        return false;
                    }
                    dontPromptErrors = query.dontAskAgain();
                }
                break;

            case ARCHIVE_FATAL:
                qCCritical(ARK) << "archive_write_header() has returned" << returnCode
                                << "with errno" << archive_errno(writer.data());
                emit error(i18nc("@info", "Fatal error, extraction aborted."));
                return false;
            default:
                qCDebug(ARK) << "archive_write_header() returned" << returnCode
                             << "which will be ignored.";
                break;
            }


            if (!extractAll && m_cachedArchiveEntryCount) {
                ++progressEntryCount;
                emit progress(float(progressEntryCount) / totalEntriesCount);
            }

            extractedEntriesCount++;
            remainingFiles.removeOne(entryName);
        } else {

            archive_read_data_skip(m_archiveReader.data());
        }
    }

    qCDebug(ARK) << "Extracted" << extractedEntriesCount << "entries";
    slotRestoreWorkingDir();
    return archive_read_close(m_archiveReader.data()) == ARCHIVE_OK;
}
