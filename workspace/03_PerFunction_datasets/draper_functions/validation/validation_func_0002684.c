Internal_Open_Font (Display *d, Object name) {
    register char *s;
    XFontStruct *p;
    Alloca_Begin;

    Get_Strsym_Stack (name, s);
    Disable_Interrupts;
    if ((p = XLoadQueryFont (d, s)) == 0)
        Primitive_Error ("cannot open font: ~s", name);
    Enable_Interrupts;
    Alloca_End;
    return p;
}
