int InputBuffer::incrementalHistorySearch(PromptBase& pi, int startChar) {
    size_t bufferSize;
    size_t ucharCount;
    int errorCode;


    if (historyIndex == historyLen - 1) {
        free(history[historyLen - 1]);
        bufferSize = sizeof(UChar32) * len + 1;
        unique_ptr<UChar8[]> tempBuffer(new UChar8[bufferSize]);
        copyString32to8(tempBuffer.get(), buf32, bufferSize);
        history[historyLen - 1] =
            reinterpret_cast<UChar8*>(strdup(reinterpret_cast<const char*>(tempBuffer.get())));
    }
    int historyLineLength = len;
    int historyLinePosition = pos;
    UChar32 emptyBuffer[1];
    char emptyWidths[1];
    InputBuffer empty(emptyBuffer, emptyWidths, 1);
    empty.refreshLine(pi);
    DynamicPrompt dp(pi, (startChar == ctrlChar('R')) ? -1 : 1);

    dp.promptPreviousLen = pi.promptPreviousLen;
    dp.promptPreviousInputLen = pi.promptPreviousInputLen;
    dynamicRefresh(
        dp, buf32, historyLineLength, historyLinePosition);


    int c;
    bool keepLooping = true;
    bool useSearchedLine = true;
    bool searchAgain = false;
    UChar32* activeHistoryLine = 0;
    while (keepLooping) {
        c = linenoiseReadChar();
        c = cleanupCtrl(c);

        switch (c) {

            case ctrlChar('A'):
            case HOME_KEY:
            case ctrlChar('B'):
            case LEFT_ARROW_KEY:
            case META + 'b':
            case META + 'B':
            case CTRL + LEFT_ARROW_KEY:
            case META + LEFT_ARROW_KEY:
            case ctrlChar('D'):
            case META + 'd':
            case META + 'D':
            case ctrlChar('E'):
            case END_KEY:
            case ctrlChar('F'):
            case RIGHT_ARROW_KEY:
            case META + 'f':
            case META + 'F':
            case CTRL + RIGHT_ARROW_KEY:
            case META + RIGHT_ARROW_KEY:
            case META + ctrlChar('H'):
            case ctrlChar('J'):
            case ctrlChar('K'):
            case ctrlChar('M'):
            case ctrlChar('N'):
            case ctrlChar('P'):
            case DOWN_ARROW_KEY:
            case UP_ARROW_KEY:
            case ctrlChar('T'):
            case ctrlChar('U'):
            case ctrlChar('W'):
            case META + 'y':
            case META + 'Y':
            case 127:
            case DELETE_KEY:
            case META + '<':
            case PAGE_UP_KEY:
            case META + '>':
            case PAGE_DOWN_KEY:
                keepLooping = false;
                break;


            case ctrlChar('C'):
            case ctrlChar('G'):
            case ctrlChar('L'):
                keepLooping = false;
                useSearchedLine = false;
                if (c != ctrlChar('L')) {
                    c = -1;
                }
                break;


            case ctrlChar('S'):
            case ctrlChar('R'):
                if (dp.searchTextLen == 0) {
                    if (previousSearchText.length()) {
                        dp.updateSearchText(previousSearchText.get());
                    }
                }
                if ((dp.direction == 1 && c == ctrlChar('R')) ||
                    (dp.direction == -1 && c == ctrlChar('S'))) {
                    dp.direction = 0 - dp.direction;
                    dp.updateSearchPrompt();
                } else {
                    searchAgain = true;
                }
                break;


#ifndef _WIN32
            case ctrlChar('Z'):
                disableRawMode();
                raise(SIGSTOP);
                enableRawMode();
                {
                    bufferSize = historyLineLength + 1;
                    unique_ptr<UChar32[]> tempUnicode(new UChar32[bufferSize]);
                    copyString8to32(tempUnicode.get(),
                                    history[historyIndex],
                                    bufferSize,
                                    ucharCount,
                                    errorCode);
                    dynamicRefresh(dp, tempUnicode.get(), historyLineLength, historyLinePosition);
                }
                continue;
                break;
#endif


            case ctrlChar('H'):
                if (dp.searchTextLen > 0) {
                    unique_ptr<UChar32[]> tempUnicode(new UChar32[dp.searchTextLen]);
                    --dp.searchTextLen;
                    dp.searchText[dp.searchTextLen] = 0;
                    copyString32(tempUnicode.get(), dp.searchText.get(), dp.searchTextLen + 1);
                    dp.updateSearchText(tempUnicode.get());
                } else {
                    beep();
                }
                break;

            case ctrlChar('Y'):
                break;

            default:
                if (!isControlChar(c) && c <= 0x0010FFFF) {
                    unique_ptr<UChar32[]> tempUnicode(new UChar32[dp.searchTextLen + 2]);
                    copyString32(tempUnicode.get(), dp.searchText.get(), dp.searchTextLen + 2);
                    tempUnicode[dp.searchTextLen] = c;
                    tempUnicode[dp.searchTextLen + 1] = 0;
                    dp.updateSearchText(tempUnicode.get());
                } else {
                    beep();
                }
        }


        if (keepLooping) {
            bufferSize = historyLineLength + 1;
            activeHistoryLine = new UChar32[bufferSize];
            copyString8to32(
                activeHistoryLine, history[historyIndex], bufferSize, ucharCount, errorCode);
            if (dp.searchTextLen > 0) {
                bool found = false;
                int historySearchIndex = historyIndex;
                int lineLength = ucharCount;
                int lineSearchPos = historyLinePosition;
                if (searchAgain) {
                    lineSearchPos += dp.direction;
                }
                searchAgain = false;
                while (true) {
                    while ((dp.direction > 0) ? (lineSearchPos < lineLength)
                                              : (lineSearchPos >= 0)) {
                        if (strncmp32(dp.searchText.get(),
                                      &activeHistoryLine[lineSearchPos],
                                      dp.searchTextLen) == 0) {
                            found = true;
                            break;
                        }
                        lineSearchPos += dp.direction;
                    }
                    if (found) {
                        historyIndex = historySearchIndex;
                        historyLineLength = lineLength;
                        historyLinePosition = lineSearchPos;
                        break;
                    } else if ((dp.direction > 0) ? (historySearchIndex < historyLen - 1)
                                                  : (historySearchIndex > 0)) {
                        historySearchIndex += dp.direction;
                        bufferSize =
                            strlen(reinterpret_cast<char*>(history[historySearchIndex])) + 1;
                        delete[] activeHistoryLine;
                        activeHistoryLine = new UChar32[bufferSize];
                        copyString8to32(activeHistoryLine,
                                        history[historySearchIndex],
                                        bufferSize,
                                        ucharCount,
                                        errorCode);
                        lineLength = ucharCount;
                        lineSearchPos = (dp.direction > 0) ? 0 : (lineLength - dp.searchTextLen);
                    } else {
                        beep();
                        break;
                    }
                };
            }
            if (activeHistoryLine) {
                delete[] activeHistoryLine;
            }
            bufferSize = historyLineLength + 1;
            activeHistoryLine = new UChar32[bufferSize];
            copyString8to32(
                activeHistoryLine, history[historyIndex], bufferSize, ucharCount, errorCode);
            dynamicRefresh(dp,
                           activeHistoryLine,
                           historyLineLength,
                           historyLinePosition);
        }
    }


    PromptBase pb;
    pb.promptChars = pi.promptIndentation;
    Utf32String tempUnicode(pb.promptChars + 1);
    copyString32(tempUnicode.get(), &pi.promptText[pi.promptLastLinePosition], pb.promptChars + 1);
    tempUnicode.initFromBuffer();
    pb.promptText = tempUnicode;
    pb.promptExtraLines = 0;
    pb.promptIndentation = pi.promptIndentation;
    pb.promptLastLinePosition = 0;
    pb.promptPreviousInputLen = historyLineLength;
    pb.promptCursorRowOffset = dp.promptCursorRowOffset;
    pb.promptScreenColumns = pi.promptScreenColumns;
    pb.promptPreviousLen = dp.promptChars;
    if (useSearchedLine && activeHistoryLine) {
        historyRecallMostRecent = true;
        copyString32(buf32, activeHistoryLine, buflen + 1);
        len = historyLineLength;
        pos = historyLinePosition;
    }
    if (activeHistoryLine) {
        delete[] activeHistoryLine;
    }
    dynamicRefresh(pb, buf32, len, pos);
    pi.promptPreviousInputLen = len;
    pi.promptCursorRowOffset = pi.promptExtraLines + pb.promptCursorRowOffset;
    previousSearchText = dp.searchText;
    return c;
}
