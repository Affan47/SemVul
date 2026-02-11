ReadCommands(CurPos &cp, const char *Name) {
    STARTFUNC("ReadCommands");
    LOG << "Name = " << (Name != NULL ? Name : "(null)") << ENDLINE;

    unsigned char obj;
    unsigned short len;
    long Cmd = NewCommand(Name);
    long cmdno;

    if (GetObj(cp, len) != CF_INT) ENDFUNCRC(-1);
    if (GetNum(cp, cmdno) == 0) ENDFUNCRC(-1);
    if (cmdno != (Cmd | CMD_EXT)) {
        fprintf(stderr, "Bad Command map %s -> %ld != %ld\n", Name, Cmd, cmdno);
        ENDFUNCRC(-1);
    }

    while ((obj = GetObj(cp, len)) != 0xFF) {
        switch (obj) {
        case CF_COMMAND:
            {

                long cnt;
                long ign;
                long cmd;


                if (GetNum(cp, cmd) == 0) ENDFUNCRC(-1);
                if (GetObj(cp, len) != CF_INT) ENDFUNCRC(-1);
                if (GetNum(cp, cnt) == 0) ENDFUNCRC(-1);
                if (GetObj(cp, len) != CF_INT) ENDFUNCRC(-1);
                if (GetNum(cp, ign) == 0) ENDFUNCRC(-1);


                if (AddCommand(Cmd, cmd, cnt, ign) == 0) {
                    if (Name == 0 || strcmp(Name, "xx") != 0) {
                        fprintf(stderr, "Bad Command Id: %ld\n", cmd);
                        ENDFUNCRC(-1);
                    }
                }
            }
            break;
        case CF_STRING:
            {
                const char *s = GetCharStr(cp, len);

                if (s == 0) ENDFUNCRC(-1);
                if (AddString(Cmd, s) == 0) ENDFUNCRC(-1);
            }
            break;
        case CF_INT:
            {
                long num;

                if (GetNum(cp, num) == 0) ENDFUNCRC(-1);
                if (AddNumber(Cmd, num) == 0) ENDFUNCRC(-1);
            }
            break;
        case CF_VARIABLE:
            {
                long num;

                if (GetNum(cp, num) == 0) ENDFUNCRC(-1);
                if (AddVariable(Cmd, num) == 0) ENDFUNCRC(-1);
            }
            break;
        case CF_CONCAT:
            if (AddConcat(Cmd) == 0) ENDFUNCRC(-1);
            break;
        case CF_END:
            ENDFUNCRC(Cmd);
        default:
            ENDFUNCRC(-1);
        }
    }
    ENDFUNCRC(-1);
}
