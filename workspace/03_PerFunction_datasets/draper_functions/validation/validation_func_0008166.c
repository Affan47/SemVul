filterEvent(const XEvent &xev) {
    if (xev.type == MappingNotify) {
        msg("MappingNotify");
        XMappingEvent xmapping = xev.xmapping;
        XRefreshKeyboardMapping(&xmapping);

        initModifiers();

        desktop->grabKeys();
        return true;
    }
    return false;
}
