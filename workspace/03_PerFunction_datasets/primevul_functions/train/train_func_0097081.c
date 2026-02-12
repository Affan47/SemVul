void InputBuffer::refreshLine(PromptBase& pi) {

    int highlight = -1;
    if (pos < len) {

        int scanDirection = 0;
        if (strchr("}])", buf32[pos]))
            scanDirection = -1;
        else if (strchr("{[(", buf32[pos]))
            scanDirection = 1;

        if (scanDirection) {
            int unmatched = scanDirection;
            for (int i = pos + scanDirection; i >= 0 && i < len; i += scanDirection) {

                if (strchr("}])", buf32[i]))
                    --unmatched;
                else if (strchr("{[(", buf32[i]))
                    ++unmatched;

                if (unmatched == 0) {
                    highlight = i;
                    break;
                }
            }
        }
    }


    int xEndOfInput, yEndOfInput;
    calculateScreenPosition(pi.promptIndentation,
                            0,
                            pi.promptScreenColumns,
                            calculateColumnPosition(buf32, len),
                            xEndOfInput,
                            yEndOfInput);


    int xCursorPos, yCursorPos;
    calculateScreenPosition(pi.promptIndentation,
                            0,
                            pi.promptScreenColumns,
                            calculateColumnPosition(buf32, pos),
                            xCursorPos,
                            yCursorPos);

#ifdef _WIN32

    CONSOLE_SCREEN_BUFFER_INFO inf;
    GetConsoleScreenBufferInfo(console_out, &inf);
    inf.dwCursorPosition.X = pi.promptIndentation;
    inf.dwCursorPosition.Y -= pi.promptCursorRowOffset - pi.promptExtraLines;
    SetConsoleCursorPosition(console_out, inf.dwCursorPosition);
    DWORD count;
    if (len < pi.promptPreviousInputLen)
        FillConsoleOutputCharacterA(
            console_out, ' ', pi.promptPreviousInputLen, inf.dwCursorPosition, &count);
    pi.promptPreviousInputLen = len;


    if (highlight == -1) {
        if (write32(1, buf32, len) == -1)
            return;
    } else {
        if (write32(1, buf32, highlight) == -1)
            return;
        setDisplayAttribute(true);
        if (write32(1, &buf32[highlight], 1) == -1)
            return;
        setDisplayAttribute(false);
        if (write32(1, buf32 + highlight + 1, len - highlight - 1) == -1)
            return;
    }


    GetConsoleScreenBufferInfo(console_out, &inf);
    inf.dwCursorPosition.X = xCursorPos;
    inf.dwCursorPosition.Y -= yEndOfInput - yCursorPos;
    SetConsoleCursorPosition(console_out, inf.dwCursorPosition);
#else
    char seq[64];
    int cursorRowMovement = pi.promptCursorRowOffset - pi.promptExtraLines;
    if (cursorRowMovement > 0) {
        snprintf(seq, sizeof seq, "\x1b[%dA", cursorRowMovement);
        if (write(1, seq, strlen(seq)) == -1)
            return;
    }

    snprintf(seq, sizeof seq, "\x1b[%dG\x1b[J", pi.promptIndentation + 1);
    if (write(1, seq, strlen(seq)) == -1)
        return;

    if (highlight == -1) {
        if (write32(1, buf32, len) == -1)
            return;
    } else {
        if (write32(1, buf32, highlight) == -1)
            return;
        setDisplayAttribute(true);
        if (write32(1, &buf32[highlight], 1) == -1)
            return;
        setDisplayAttribute(false);
        if (write32(1, buf32 + highlight + 1, len - highlight - 1) == -1)
            return;
    }


    if (xEndOfInput == 0 && yEndOfInput > 0)
        if (write(1, "\n", 1) == -1)
            return;


    cursorRowMovement = yEndOfInput - yCursorPos;
    if (cursorRowMovement > 0) {
        snprintf(seq, sizeof seq, "\x1b[%dA", cursorRowMovement);
        if (write(1, seq, strlen(seq)) == -1)
            return;
    }

    snprintf(seq, sizeof seq, "\x1b[%dG", xCursorPos + 1);
    if (write(1, seq, strlen(seq)) == -1)
        return;
#endif

    pi.promptCursorRowOffset = pi.promptExtraLines + yCursorPos;
}
