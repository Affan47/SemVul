mangleString(char *utf8) {
    int len = utf8Len(utf8);
    unsigned short *unicode = sysMalloc(len * 2);
    char *mangled, *mngldPtr;
    int i, mangledLen = 0;

    convertUtf8(utf8, unicode);


    for(i = 0; i < len; i++) {
        unsigned short c = unicode[i];
        switch(c) {
            case '_':
            case ';':
            case '[':
                mangledLen += 2;
                break;

           default:
                mangledLen += isalnum(c) ? 1 : 6;
                break;
        }
    }

    mangled = mngldPtr = sysMalloc(mangledLen + 1);


    for(i = 0; i < len; i++) {
        unsigned short c = unicode[i];
        switch(c) {
            case '_':
                *mngldPtr++ = '_';
                *mngldPtr++ = '1';
                break;
            case ';':
                *mngldPtr++ = '_';
                *mngldPtr++ = '2';
                break;
            case '[':
                *mngldPtr++ = '_';
                *mngldPtr++ = '3';
                break;

            case '/':
                *mngldPtr++ = '_';
                break;

            default:
                if(isalnum(c))
                    *mngldPtr++ = c;
                else
                    mngldPtr += sprintf(mngldPtr, "_0%04x", c);
                break;
        }
    }

    *mngldPtr = '\0';

    sysFree(unicode);
    return mangled;
}
