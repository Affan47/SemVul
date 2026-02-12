static void dynamicRefresh(PromptBase& pi, UChar32* buf32, int len, int pos) {

    int xEndOfPrompt, yEndOfPrompt;
    calculateScreenPosition(
        0, 0, pi.promptScreenColumns, pi.promptChars, xEndOfPrompt, yEndOfPrompt);
    pi.promptIndentation = xEndOfPrompt;


    int xEndOfInput, yEndOfInput;
    calculateScreenPosition(xEndOfPrompt,
                            yEndOfPrompt,
                            pi.promptScreenColumns,
                            calculateColumnPosition(buf32, len),
                            xEndOfInput,
                            yEndOfInput);


    int xCursorPos, yCursorPos;
    calculateScreenPosition(xEndOfPrompt,
                            yEndOfPrompt,
                            pi.promptScreenColumns,
                            calculateColumnPosition(buf32, pos),
                            xCursorPos,
                            yCursorPos);

#ifdef _WIN32

    CONSOLE_SCREEN_BUFFER_INFO inf;
    GetConsoleScreenBufferInfo(console_out, &inf);
    inf.dwCursorPosition.X = 0;
    inf.dwCursorPosition.Y -= pi.promptCursorRowOffset ;
    SetConsoleCursorPosition(console_out, inf.dwCursorPosition);
    DWORD count;
    FillConsoleOutputCharacterA(console_out,
                                ' ',
                                pi.promptPreviousLen + pi.promptPreviousInputLen,
                                inf.dwCursorPosition,
                                &count);
    pi.promptPreviousLen = pi.promptIndentation;
    pi.promptPreviousInputLen = len;


    if (write32(1, pi.promptText.get(), pi.promptChars) == -1)
        return;


    if (write32(1, buf32, len) == -1)
        return;


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

    snprintf(seq, sizeof seq, "\x1b[1G\x1b[J");
    if (write(1, seq, strlen(seq)) == -1)
        return;


    if (write32(1, pi.promptText.get(), pi.promptChars) == -1)
        return;


    if (write32(1, buf32, len) == -1)
        return;


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
