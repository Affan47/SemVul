presentWindows(WId controller, const QList<WId> &ids)
{
#ifdef Q_WS_X11
    const int numWindows = ids.count();
    QVarLengthArray<long, 32> data(numWindows);
    int actualCount = 0;

    for (int i = 0; i < numWindows; ++i) {
        data[i] = ids.at(i);
        ++actualCount;

    }

    if (actualCount != numWindows) {
        data.resize(actualCount);
    }

    if (!data.isEmpty()) {
        Display *dpy = QX11Info::display();
        Atom atom = XInternAtom(dpy, "_KDE_PRESENT_WINDOWS_GROUP", False);
        XChangeProperty(dpy, controller, atom, atom, 32, PropModeReplace,
                        reinterpret_cast<unsigned char *>(data.data()), data.size());
    }
#endif
}
