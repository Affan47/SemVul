createTempManager()
{
    KBookmarkManager* mgr = new KBookmarkManager();
    s_pSelf->append( mgr );
    return mgr;
}
