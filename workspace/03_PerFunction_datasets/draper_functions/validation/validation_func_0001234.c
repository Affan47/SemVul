saveGame()
{
    if ( !m_dealer )
        return;

    KFileDialog dialog( dialogUrl, "", this, 0 );
    dialog.setOperationMode( KFileDialog::Saving );
    dialog.setMimeFilter( QStringList() << saveFileMimeType << legacySaveFileMimeType, saveFileMimeType );
    dialog.setConfirmOverwrite( true );
    dialog.setCaption( i18n("Save") );
    if ( dialog.exec() != KFileDialog::Accepted )
        return;

    KUrl url = dialog.selectedUrl();
    if ( url.isEmpty() )
        return;

    QFile localFile;
    KTemporaryFile tempFile;
    if ( url.isLocalFile() )
    {
        localFile.setFileName( url.toLocalFile() );
        if ( !localFile.open( QFile::WriteOnly ) )
        {
            KMessageBox::error( this, i18n("Error opening file for writing. Saving failed.") );
            return;
        }
    }
    else
    {
        if ( !tempFile.open() )
        {
            KMessageBox::error( this, i18n("Unable to create temporary file. Saving failed.") );
            return;
        }
    }
    QFile & file = url.isLocalFile() ? localFile : tempFile;

    if ( dialog.currentFilterMimeType()->is( legacySaveFileMimeType ) )
    {
        m_dealer->saveLegacyFile( &file );
    }
    else
    {
        m_dealer->saveFile( &file );
    }

    file.close();

    if ( !url.isLocalFile() && !KIO::NetAccess::upload( file.fileName(), url, this ) )
    {
        KMessageBox::error( this, i18n("Error uploading file. Saving failed.") );
        return;
    }

    m_recentFilesAction->addUrl( url );
}
