x11_create_window(Display *dpy, guint w, guint h, Visual *vis, Colormap cmap)
{
    Window rootwin, win;
    int screen, depth;
    XSetWindowAttributes xswa;
    unsigned long xswa_mask;
    XWindowAttributes wattr;
    unsigned long black_pixel;

    screen      = DefaultScreen(dpy);
    rootwin     = RootWindow(dpy, screen);
    black_pixel = BlackPixel(dpy, screen);

    if (!vis)
        vis = DefaultVisual(dpy, screen);

    XGetWindowAttributes(dpy, rootwin, &wattr);
    depth = wattr.depth;
    if (depth != 15 && depth != 16 && depth != 24 && depth != 32)
        depth = 24;

    xswa_mask             = CWBorderPixel | CWBackPixel;
    xswa.border_pixel     = black_pixel;
    xswa.background_pixel = black_pixel;

    if (cmap) {
        xswa_mask        |= CWColormap;
        xswa.colormap     = cmap;
    }

    win = XCreateWindow(
        dpy,
        rootwin,
        0, 0, w, h,
        0,
        depth,
        InputOutput,
        vis,
        xswa_mask, &xswa
    );
    if (!win)
        return None;

    XSelectInput(dpy, win, x11_event_mask);
    return win;
}
