updateBackground(Window win, const FbTk::Color &bg_color) {

    FbTk::FbWindow* fbwin= find(win);
    if (!fbwin )
        return;


    if (m_use_pixmap) {
        XWMHints *hints = XGetWMHints(FbTk::App::instance()->display(), win);
        if (hints && (hints->flags & IconPixmapHint) && hints->icon_pixmap != 0) {
            FbTk::FbPixmap fbpix;
            fbpix.copy(hints->icon_pixmap);
            fbpix.scale(fbwin->width(), fbwin->height());
            fbwin->setBackgroundPixmap(fbpix.drawable());
        }
        else
            fbwin->setBackgroundColor(bg_color);

        XFree(hints);
    }
    else
        fbwin->setBackgroundColor(bg_color);
}
