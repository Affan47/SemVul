handleCrossing(const XCrossingEvent &crossing) {
    if (fSelected && fEnabled) {
        if (crossing.type == EnterNotify) {
            if (!fPopup)
                setArmed(true, true);
        } else if (crossing.type == LeaveNotify) {
            if (!fPopup)
                setArmed(false, true);
        }
    }

    if (fEnabled) {
        if (crossing.type == EnterNotify) {
            setOver(true);
        } else if (crossing.type == LeaveNotify) {
            setOver(false);
        }
    }

    YWindow::handleCrossing(crossing);
}
