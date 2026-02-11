init_xinerama(void)
{
#ifdef XINERAMA
        int evbase, errbase, major, minor;

        rp_have_xinerama = 0;

        if (xine_screens) XFree(xine_screens);

        if (!XineramaQueryExtension(dpy, &evbase, &errbase)) {
                return;
        }

        if (!XineramaQueryVersion(dpy, &major, &minor) != Success) {
                return;
        }

        if (major != 1) {
                fprintf (stderr, "Warning: Xinerama version %d.%d not supported\n", major, minor);
                return;
        }

        if (!XineramaIsActive(dpy)) {
                return;
        }

        xine_screens = XineramaQueryScreens(dpy, &xine_screen_count);
        if ((xine_screens == NULL) || (xine_screen_count < 2)) {
                return;
        }

        rp_have_xinerama = 1;
#else
        rp_have_xinerama = 0;
#endif
}
