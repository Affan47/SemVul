P_Lookup_String (Object d, Object k, Object mask) {
    XKeyEvent e;
    char buf[1024];
    register int len;
    KeySym keysym_return;
    XComposeStatus status_return;

    Check_Type (d, T_Display);
    e.display = DISPLAY(d)->dpy;
    e.keycode = Get_Integer (k);
    e.state = Symbols_To_Bits (mask, 1, State_Syms);
    Disable_Interrupts;
    len = XLookupString (&e, buf, 1024, &keysym_return, &status_return);
    Enable_Interrupts;
    return Make_String (buf, len);
}
