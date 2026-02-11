setAbove(YFrameWindow *aboveFrame) {
    if (aboveFrame != 0 &&
        getActiveLayer() != aboveFrame->getActiveLayer())
    {
        MSG(("ignore z-order change between layers: win=0x%lX (above: 0x%lX) ", handle(), aboveFrame->client()->handle()));
        return;
    }

#ifdef DEBUG
    if (debug_z) dumpZorder("before setAbove", this, aboveFrame);
#endif
    if (aboveFrame != next() && aboveFrame != this) {
        if (prev())
            prev()->setNext(next());
        else
            manager->setTop(getActiveLayer(), next());

        if (next())
            next()->setPrev(prev());
        else
            manager->setBottom(getActiveLayer(), prev());

        setNext(aboveFrame);
        if (next()) {
            setPrev(next()->prev());
            next()->setPrev(this);
        } else {
            setPrev(manager->bottom(getActiveLayer()));
            manager->setBottom(getActiveLayer(), this);
        }
        if (prev())
            prev()->setNext(this);
        else
            manager->setTop(getActiveLayer(), this);
#ifdef DEBUG
        if (debug_z) dumpZorder("after setAbove", this, aboveFrame);
#endif
    }
    manager->updateFullscreenLayer();
}
