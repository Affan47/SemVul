handleGrabEvent(YWindow *winx, XEvent &xev) {
    union {
        YWindow *ptr;
        XPointer xptr;
    } win = { winx };

    PRECONDITION(win.ptr != 0);
    if (fGrabTree) {
        if (xev.xbutton.subwindow != None) {
            if (XFindContext(display(),
                         xev.xbutton.subwindow,
                         windowContext,
                             &(win.xptr)) != 0)
            {
                if (xev.type == EnterNotify || xev.type == LeaveNotify)
                    win.ptr = 0;
                else
                    win.ptr = fGrabWindow;
            }
        } else {
            if (XFindContext(display(),
                             xev.xbutton.window,
                             windowContext,
                             &(win.xptr)) != 0)
            {
                if (xev.type == EnterNotify || xev.type == LeaveNotify)
                    win.ptr = 0;
                else
                    win.ptr = fGrabWindow;
            }
        }
        if (win.ptr == 0)
            return ;
        {
            YWindow *p = win.ptr;
            while (p) {
                if (p == fXGrabWindow)
                    break;
                p = p->parent();
            }
            if (p == 0) {
                if (xev.type == EnterNotify || xev.type == LeaveNotify)
                    return ;
                else
                    win.ptr = fGrabWindow;
            }
        }
        if (xev.type == EnterNotify || xev.type == LeaveNotify)
            if (win.ptr != fGrabWindow)
                return ;
        if (fGrabWindow != fXGrabWindow)
            win.ptr = fGrabWindow;
    }
    dispatchEvent(win.ptr, xev);
}
