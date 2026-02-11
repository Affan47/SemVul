pager_event_filter( XEvent *xev, GdkEvent *event, pager_priv *pg)
{
    ENTER;
    if (xev->type == PropertyNotify )
        pager_propertynotify(pg, xev);
    else if (xev->type == ConfigureNotify )
        pager_configurenotify(pg, xev);
    RET(GDK_FILTER_CONTINUE);
}
