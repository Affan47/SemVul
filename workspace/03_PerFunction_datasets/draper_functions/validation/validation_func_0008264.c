extendedStrut() const
{
#if !defined(KDE_NO_WARNING_OUTPUT)
    if (!(d->info->passedProperties()[ NETWinInfo::PROTOCOLS2 ] & NET::WM2ExtendedStrut))
        kWarning(176) << "Pass NET::WM2ExtendedStrut to KWindowInfo";
#endif
    NETExtendedStrut ext = d->info->extendedStrut();
    NETStrut str = d->info->strut();
    if( ext.left_width == 0 && ext.right_width == 0 && ext.top_width == 0 && ext.bottom_width == 0
        && ( str.left != 0 || str.right != 0 || str.top != 0 || str.bottom != 0 )) {

        if( str.left != 0 ) {
            ext.left_width = str.left;
            ext.left_start = 0;
            ext.left_end = XDisplayHeight( QX11Info::display(), DefaultScreen( QX11Info::display()));
        }
        if( str.right != 0 ) {
            ext.right_width = str.right;
            ext.right_start = 0;
            ext.right_end = XDisplayHeight( QX11Info::display(), DefaultScreen( QX11Info::display()));
        }
        if( str.top != 0 ) {
            ext.top_width = str.top;
            ext.top_start = 0;
            ext.top_end = XDisplayWidth( QX11Info::display(), DefaultScreen( QX11Info::display()));
        }
        if( str.bottom != 0 ) {
            ext.bottom_width = str.bottom;
            ext.bottom_start = 0;
            ext.bottom_end = XDisplayWidth( QX11Info::display(), DefaultScreen( QX11Info::display()));
        }
    }
    return ext;
}
