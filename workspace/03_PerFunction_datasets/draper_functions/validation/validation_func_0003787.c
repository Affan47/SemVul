P_Set_Pointer_Mapping (Object dpy, Object map) {
    register int i, n;
    register unsigned char *p;
    Object ret;
    Alloca_Begin;

    Check_Type (dpy, T_Display);
    Check_Type (map, T_Vector);
    n = VECTOR(map)->size;
    Alloca (p, unsigned char*, n);
    for (i = 0; i < n; i++)
        p[i] = Get_Integer (VECTOR(map)->data[i]);
    ret = XSetPointerMapping (DISPLAY(dpy)->dpy, p, n) == MappingSuccess ?
        True : False;
    Alloca_End;
    return ret;
}
