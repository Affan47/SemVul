toString() const {
    char buf[64] ;
    switch (type) {
    case T_INTEGER:
        sprintf (buf, "%lld", integer) ;
        break ;
    case T_REAL:
        sprintf (buf, "%g", real) ;
        break ;
    case T_BYTE:
        buf[0] = (char)integer ;
        return string (buf, 1) ;
        break ;
    case T_CHAR:
        sprintf (buf, "%c", (char)integer) ;
        break ;
    case T_BOOL:
        sprintf (buf, "%s", integer ? "true":"false") ;
        break ;
    }
    return buf ;
}
