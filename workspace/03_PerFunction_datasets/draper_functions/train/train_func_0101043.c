P_Read_String (int argc, Object *argv) {
    Object port;
    register FILE *f;
    register int c, str;

    port = argc == 1 ? argv[0] : Curr_Input_Port;
    Check_Input_Port (port);
    f = PORT(port)->file;
    str = PORT(port)->flags & P_STRING;
    Read_Reset ();
    while (1) {
        Reader_Getc;
        if (c == '\n' || c == EOF)
            break;
        Read_Store (c);
    }
    Reader_Tweak_Stream;
    return c == EOF ? Eof : Make_String (Read_Buf, Read_Size);
}
