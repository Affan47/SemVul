CmdBreveChar(int code)
{
    int n = RtfFontNumber("STIXGeneral");
    char *cParam = getBraceParam();

    switch (cParam[0]) {
        case 'A':
            putUnicodeChar(0x01,0x02,'A');
            break;
        case 'a':
            putUnicodeChar(0x01,0x03,'a');
            break;
        case 'E':
            putUnicodeChar(0x01,0x14,'E');
            break;
        case 'e':
            putUnicodeChar(0x01,0x15,'e');
            break;
        case 'G':
            putUnicodeChar(0x01,0x1e,'G');
            break;
        case 'g':
            putUnicodeChar(0x01,0x1f,'g');
            break;
        case 'I':
            putUnicodeChar(0x01,0x2c,'I');
            break;
        case 'i':
            putUnicodeChar(0x01,0x2d,'i');
            break;
        case 'O':
            putUnicodeChar(0x01,0x4e,'O');
            break;
        case 'o':
            putUnicodeChar(0x01,0x4f,'o');
            break;
        case 'U':
            putUnicodeChar(0x01,0x6c,'U');
            break;
        case 'c':
            putUnicodeChar(0x01,0x0D,'c');
            break;
        case '\0':
            putUnicodeChar(0x02,0xD8,'u');
            break;
        default:
            fprintRTF("{\\f%d",n);
            fprintRTF("\\u774u}");
            ConvertString(cParam);
            break;
    }

    free(cParam);
}
