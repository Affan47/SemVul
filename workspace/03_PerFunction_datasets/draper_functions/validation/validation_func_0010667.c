checkX11Extension(const std::string& ext)
{
#ifdef HAVE_X11
#ifndef GDK_DISPLAY
	#define GDK_DISPLAY() (GDK_DISPLAY_XDISPLAY(gdk_display_get_default()))
#endif
    int n = 0;
    char **extlist = XListExtensions(GDK_DISPLAY(), &n);

    if (extlist) {
        for (int i = 0; i < n; i++) {
            if (std::strncmp(ext.c_str(), extlist[i], ext.size()) == 0) {
                return true;
            }
        }
    }
#endif

    return false;
}
