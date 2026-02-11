managerForExternalFile( const QString& bookmarksFile )
{
    KBookmarkManager* mgr(0);
    {
        QReadLocker readLock(&s_pSelf->lock);
        mgr = lookupExisting(bookmarksFile);
        if (mgr) {
            return mgr;
        }
    }

    QWriteLocker writeLock(&s_pSelf->lock);
    mgr = lookupExisting(bookmarksFile);
    if (mgr) {
        return mgr;
    }

    mgr = new KBookmarkManager( bookmarksFile );
    s_pSelf->append( mgr );
    return mgr;
}
