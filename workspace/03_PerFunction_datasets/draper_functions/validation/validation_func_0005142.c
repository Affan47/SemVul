overlays() const
{
    if (!d)
        return QStringList();

    QStringList names = d->m_entry.stringValue( KIO::UDSEntry::UDS_ICON_OVERLAY_NAMES ).split(',');
    if ( d->m_bLink ) {
        names.append("emblem-symbolic-link");
    }

    if ( !S_ISDIR( d->m_fileMode )
         && !isReadable()) {
        names.append("object-locked");
    }

    if ( checkDesktopFile(*this, false) ) {
        KDesktopFile cfg( localPath() );
        const KConfigGroup group = cfg.desktopGroup();


        if ( group.hasKey( "Exec" ) && !KDesktopFile::isAuthorizedDesktopFile( localPath() ) ) {
            names.append( "emblem-important" );
        }

        if (cfg.hasDeviceType()) {
            const QString dev = cfg.readDevice();
            if (!dev.isEmpty()) {
                KMountPoint::Ptr mountPoint = KMountPoint::currentMountPoints().findByDevice(dev);
                if (mountPoint)
                    names.append("emblem-mounted");
            }
        }
    }

    if ( isHidden() ) {
        names.append("hidden");
    }

#ifndef Q_OS_WIN
    if( S_ISDIR( d->m_fileMode ) && d->m_bIsLocalUrl)
    {
        if (KSambaShare::instance()->isDirectoryShared( d->m_url.toLocalFile() ) ||
            KNFSShare::instance()->isDirectoryShared( d->m_url.toLocalFile() ))
        {

            names.append("network-workgroup");
        }
    }
#endif

    if ( d->m_pMimeType && d->m_url.fileName().endsWith( QLatin1String( ".gz" ) ) &&
         d->m_pMimeType->is("application/x-gzip") ) {
        names.append("application-zip");
    }

    return names;
}
