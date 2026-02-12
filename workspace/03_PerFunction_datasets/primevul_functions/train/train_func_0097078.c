void linenoisePreloadBuffer(const char* preloadText) {
    if (!preloadText) {
        return;
    }
    int bufferSize = strlen(preloadText) + 1;
    unique_ptr<char[]> tempBuffer(new char[bufferSize]);
    strncpy(&tempBuffer[0], preloadText, bufferSize);


    char* pIn = &tempBuffer[0];
    char* pOut = pIn;
    bool controlsStripped = false;
    bool whitespaceSeen = false;
    while (*pIn) {
        unsigned char c = *pIn++;
        if ('\r' == c) {
            continue;
        }
        if ('\n' == c || '\t' == c) {
            whitespaceSeen = true;
            continue;
        }
        if (isControlChar(c)) {
            controlsStripped = true;
            *pOut++ = ' ';
            continue;
        }
        if (whitespaceSeen) {
            *pOut++ = ' ';
            whitespaceSeen = false;
        }
        *pOut++ = c;
    }
    *pOut = 0;
    int processedLength = pOut - tempBuffer.get();
    bool lineTruncated = false;
    if (processedLength > (LINENOISE_MAX_LINE - 1)) {
        lineTruncated = true;
        tempBuffer[LINENOISE_MAX_LINE - 1] = 0;
    }
    preloadedBufferContents = tempBuffer.get();
    if (controlsStripped) {
        preloadErrorMessage += " [Edited line: control characters were converted to spaces]\n";
    }
    if (lineTruncated) {
        preloadErrorMessage += " [Edited line: the line length was reduced from ";
        char buf[128];
        snprintf(buf, sizeof(buf), "%d to %d]\n", processedLength, (LINENOISE_MAX_LINE - 1));
        preloadErrorMessage += buf;
    }
}
