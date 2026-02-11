attachSignals(Focusable &win) {
    if (m_parent == NULL)
        return;

    FluxboxWindow *fbwin = win.fbwindow();


    FbTk::RefCount<FbTk::SignalTracker> &tracker = m_signal_map[&win];
    if (! tracker) {

        tracker.reset(new SignalTracker);
        tracker->join(win.titleSig(), MemFunSelectArg1(*this, &FocusableList::updateTitle));
        tracker->join(win.dieSig(), MemFun(*this, &FocusableList::remove));
        if(fbwin) {
            tracker->join(fbwin->workspaceSig(), MemFun(*this, &FocusableList::windowUpdated));
            tracker->join(fbwin->stateSig(), MemFun(*this, &FocusableList::windowUpdated));
            tracker->join(fbwin->layerSig(), MemFun(*this, &FocusableList::windowUpdated));

        }
    }
}
