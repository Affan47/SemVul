int InputBuffer::getInputLine(PromptBase& pi) {

    if (len > 0) {
        size_t bufferSize = sizeof(UChar32) * len + 1;
        unique_ptr<char[]> tempBuffer(new char[bufferSize]);
        copyString32to8(reinterpret_cast<UChar8*>(tempBuffer.get()), buf32, bufferSize);
        linenoiseHistoryAdd(tempBuffer.get());
    } else {
        linenoiseHistoryAdd("");
    }
    historyIndex = historyLen - 1;
    historyRecallMostRecent = false;


    if (write32(1, pi.promptText.get(), pi.promptChars) == -1)
        return -1;

#ifndef _WIN32

    if (pi.promptIndentation == 0 && pi.promptExtraLines > 0)
        if (write(1, "\n", 1) == -1)
            return -1;
#endif


    pi.promptCursorRowOffset = pi.promptExtraLines;


    killRing.lastAction = KillRing::actionOther;


    int terminatingKeystroke = -1;


    if (len > 0) {
        refreshLine(pi);
    }


    while (true) {
        int c;
        if (terminatingKeystroke == -1) {
            c = linenoiseReadChar();
        } else {
            c = terminatingKeystroke;
            terminatingKeystroke = -1;
        }
        c = cleanupCtrl(c);

        if (c == 0) {
            return len;
        }

        if (c == -1) {
            refreshLine(pi);
            continue;
        }

        if (c == -2) {
            if (write32(1, pi.promptText.get(), pi.promptChars) == -1)
                return -1;
            refreshLine(pi);
            continue;
        }


        if (c == ctrlChar('I') && completionCallback) {
            if (pos == 0)
                continue;


            killRing.lastAction = KillRing::actionOther;
            historyRecallMostRecent = false;


            c = completeLine(pi);

            if (c < 0)
                return len;

            if (c == 0)
                continue;


        }

        switch (c) {
            case ctrlChar('A'):
            case HOME_KEY:
                killRing.lastAction = KillRing::actionOther;
                pos = 0;
                refreshLine(pi);
                break;

            case ctrlChar('B'):
            case LEFT_ARROW_KEY:
                killRing.lastAction = KillRing::actionOther;
                if (pos > 0) {
                    --pos;
                    refreshLine(pi);
                }
                break;

            case META + 'b':
            case META + 'B':
            case CTRL + LEFT_ARROW_KEY:
            case META + LEFT_ARROW_KEY:
                killRing.lastAction = KillRing::actionOther;
                if (pos > 0) {
                    while (pos > 0 && !isCharacterAlphanumeric(buf32[pos - 1])) {
                        --pos;
                    }
                    while (pos > 0 && isCharacterAlphanumeric(buf32[pos - 1])) {
                        --pos;
                    }
                    refreshLine(pi);
                }
                break;

            case ctrlChar('C'):
                killRing.lastAction = KillRing::actionOther;
                historyRecallMostRecent = false;
                errno = EAGAIN;
                --historyLen;
                free(history[historyLen]);


                pos = len;
                refreshLine(pi);
                if (write(1, "^C", 2) == -1)
                    return -1;
                return -1;

            case META + 'c':
            case META + 'C':
                killRing.lastAction = KillRing::actionOther;
                historyRecallMostRecent = false;
                if (pos < len) {
                    while (pos < len && !isCharacterAlphanumeric(buf32[pos])) {
                        ++pos;
                    }
                    if (pos < len && isCharacterAlphanumeric(buf32[pos])) {
                        if (buf32[pos] >= 'a' && buf32[pos] <= 'z') {
                            buf32[pos] += 'A' - 'a';
                        }
                        ++pos;
                    }
                    while (pos < len && isCharacterAlphanumeric(buf32[pos])) {
                        if (buf32[pos] >= 'A' && buf32[pos] <= 'Z') {
                            buf32[pos] += 'a' - 'A';
                        }
                        ++pos;
                    }
                    refreshLine(pi);
                }
                break;


            case ctrlChar('D'):
                killRing.lastAction = KillRing::actionOther;
                if (len > 0 && pos < len) {
                    historyRecallMostRecent = false;
                    memmove(buf32 + pos, buf32 + pos + 1, sizeof(UChar32) * (len - pos));
                    --len;
                    refreshLine(pi);
                } else if (len == 0) {
                    --historyLen;
                    free(history[historyLen]);
                    return -1;
                }
                break;

            case META + 'd':
            case META + 'D':
                if (pos < len) {
                    historyRecallMostRecent = false;
                    int endingPos = pos;
                    while (endingPos < len && !isCharacterAlphanumeric(buf32[endingPos])) {
                        ++endingPos;
                    }
                    while (endingPos < len && isCharacterAlphanumeric(buf32[endingPos])) {
                        ++endingPos;
                    }
                    killRing.kill(&buf32[pos], endingPos - pos, true);
                    memmove(
                        buf32 + pos, buf32 + endingPos, sizeof(UChar32) * (len - endingPos + 1));
                    len -= endingPos - pos;
                    refreshLine(pi);
                }
                killRing.lastAction = KillRing::actionKill;
                break;

            case ctrlChar('E'):
            case END_KEY:
                killRing.lastAction = KillRing::actionOther;
                pos = len;
                refreshLine(pi);
                break;

            case ctrlChar('F'):
            case RIGHT_ARROW_KEY:
                killRing.lastAction = KillRing::actionOther;
                if (pos < len) {
                    ++pos;
                    refreshLine(pi);
                }
                break;

            case META + 'f':
            case META + 'F':
            case CTRL + RIGHT_ARROW_KEY:
            case META + RIGHT_ARROW_KEY:
                killRing.lastAction = KillRing::actionOther;
                if (pos < len) {
                    while (pos < len && !isCharacterAlphanumeric(buf32[pos])) {
                        ++pos;
                    }
                    while (pos < len && isCharacterAlphanumeric(buf32[pos])) {
                        ++pos;
                    }
                    refreshLine(pi);
                }
                break;

            case ctrlChar('H'):
                killRing.lastAction = KillRing::actionOther;
                if (pos > 0) {
                    historyRecallMostRecent = false;
                    memmove(buf32 + pos - 1, buf32 + pos, sizeof(UChar32) * (1 + len - pos));
                    --pos;
                    --len;
                    refreshLine(pi);
                }
                break;


            case META + ctrlChar('H'):
                if (pos > 0) {
                    historyRecallMostRecent = false;
                    int startingPos = pos;
                    while (pos > 0 && !isCharacterAlphanumeric(buf32[pos - 1])) {
                        --pos;
                    }
                    while (pos > 0 && isCharacterAlphanumeric(buf32[pos - 1])) {
                        --pos;
                    }
                    killRing.kill(&buf32[pos], startingPos - pos, false);
                    memmove(buf32 + pos,
                            buf32 + startingPos,
                            sizeof(UChar32) * (len - startingPos + 1));
                    len -= startingPos - pos;
                    refreshLine(pi);
                }
                killRing.lastAction = KillRing::actionKill;
                break;

            case ctrlChar('J'):
            case ctrlChar('M'):
                killRing.lastAction = KillRing::actionOther;


                pos = len;
                refreshLine(pi);
                historyPreviousIndex = historyRecallMostRecent ? historyIndex : -2;
                --historyLen;
                free(history[historyLen]);
                return len;

            case ctrlChar('K'):
                killRing.kill(&buf32[pos], len - pos, true);
                buf32[pos] = '\0';
                len = pos;
                refreshLine(pi);
                killRing.lastAction = KillRing::actionKill;
                historyRecallMostRecent = false;
                break;

            case ctrlChar('L'):
                clearScreen(pi);
                break;

            case META + 'l':
            case META + 'L':
                killRing.lastAction = KillRing::actionOther;
                if (pos < len) {
                    historyRecallMostRecent = false;
                    while (pos < len && !isCharacterAlphanumeric(buf32[pos])) {
                        ++pos;
                    }
                    while (pos < len && isCharacterAlphanumeric(buf32[pos])) {
                        if (buf32[pos] >= 'A' && buf32[pos] <= 'Z') {
                            buf32[pos] += 'a' - 'A';
                        }
                        ++pos;
                    }
                    refreshLine(pi);
                }
                break;

            case ctrlChar('N'):
            case ctrlChar('P'):
            case DOWN_ARROW_KEY:
            case UP_ARROW_KEY:
                killRing.lastAction = KillRing::actionOther;


                if (historyIndex == historyLen - 1) {
                    free(history[historyLen - 1]);
                    size_t tempBufferSize = sizeof(UChar32) * len + 1;
                    unique_ptr<UChar8[]> tempBuffer(new UChar8[tempBufferSize]);
                    copyString32to8(tempBuffer.get(), buf32, tempBufferSize);
                    history[historyLen - 1] = reinterpret_cast<UChar8*>(
                        strdup(reinterpret_cast<const char*>(tempBuffer.get())));
                }
                if (historyLen > 1) {
                    if (c == UP_ARROW_KEY) {
                        c = ctrlChar('P');
                    }
                    if (historyPreviousIndex != -2 && c != ctrlChar('P')) {
                        historyIndex = 1 + historyPreviousIndex;
                    } else {
                        historyIndex += (c == ctrlChar('P')) ? -1 : 1;
                    }
                    historyPreviousIndex = -2;
                    if (historyIndex < 0) {
                        historyIndex = 0;
                        break;
                    } else if (historyIndex >= historyLen) {
                        historyIndex = historyLen - 1;
                        break;
                    }
                    historyRecallMostRecent = true;
                    size_t ucharCount;
                    int errorCode;
                    copyString8to32(buf32, history[historyIndex], buflen, ucharCount, errorCode);
                    len = pos = ucharCount;
                    refreshLine(pi);
                }
                break;

            case ctrlChar('R'):
            case ctrlChar('S'):
                terminatingKeystroke = incrementalHistorySearch(pi, c);
                break;

            case ctrlChar('T'):
                killRing.lastAction = KillRing::actionOther;
                if (pos > 0 && len > 1) {
                    historyRecallMostRecent = false;
                    size_t leftCharPos = (pos == len) ? pos - 2 : pos - 1;
                    char aux = buf32[leftCharPos];
                    buf32[leftCharPos] = buf32[leftCharPos + 1];
                    buf32[leftCharPos + 1] = aux;
                    if (pos != len)
                        ++pos;
                    refreshLine(pi);
                }
                break;

            case ctrlChar('U'):
                if (pos > 0) {
                    historyRecallMostRecent = false;
                    killRing.kill(&buf32[0], pos, false);
                    len -= pos;
                    memmove(buf32, buf32 + pos, sizeof(UChar32) * (len + 1));
                    pos = 0;
                    refreshLine(pi);
                }
                killRing.lastAction = KillRing::actionKill;
                break;

            case META + 'u':
            case META + 'U':
                killRing.lastAction = KillRing::actionOther;
                if (pos < len) {
                    historyRecallMostRecent = false;
                    while (pos < len && !isCharacterAlphanumeric(buf32[pos])) {
                        ++pos;
                    }
                    while (pos < len && isCharacterAlphanumeric(buf32[pos])) {
                        if (buf32[pos] >= 'a' && buf32[pos] <= 'z') {
                            buf32[pos] += 'A' - 'a';
                        }
                        ++pos;
                    }
                    refreshLine(pi);
                }
                break;


            case ctrlChar('W'):
                if (pos > 0) {
                    historyRecallMostRecent = false;
                    int startingPos = pos;
                    while (pos > 0 && buf32[pos - 1] == ' ') {
                        --pos;
                    }
                    while (pos > 0 && buf32[pos - 1] != ' ') {
                        --pos;
                    }
                    killRing.kill(&buf32[pos], startingPos - pos, false);
                    memmove(buf32 + pos,
                            buf32 + startingPos,
                            sizeof(UChar32) * (len - startingPos + 1));
                    len -= startingPos - pos;
                    refreshLine(pi);
                }
                killRing.lastAction = KillRing::actionKill;
                break;

            case ctrlChar('Y'):
                historyRecallMostRecent = false;
                {
                    Utf32String* restoredText = killRing.yank();
                    if (restoredText) {
                        bool truncated = false;
                        size_t ucharCount = restoredText->length();
                        if (ucharCount > static_cast<size_t>(buflen - len)) {
                            ucharCount = buflen - len;
                            truncated = true;
                        }
                        memmove(buf32 + pos + ucharCount,
                                buf32 + pos,
                                sizeof(UChar32) * (len - pos + 1));
                        memmove(buf32 + pos, restoredText->get(), sizeof(UChar32) * ucharCount);
                        pos += ucharCount;
                        len += ucharCount;
                        refreshLine(pi);
                        killRing.lastAction = KillRing::actionYank;
                        killRing.lastYankSize = ucharCount;
                        if (truncated) {
                            beep();
                        }
                    } else {
                        beep();
                    }
                }
                break;

            case META + 'y':
            case META + 'Y':
                if (killRing.lastAction == KillRing::actionYank) {
                    historyRecallMostRecent = false;
                    Utf32String* restoredText = killRing.yankPop();
                    if (restoredText) {
                        bool truncated = false;
                        size_t ucharCount = restoredText->length();
                        if (ucharCount >
                            static_cast<size_t>(killRing.lastYankSize + buflen - len)) {
                            ucharCount = killRing.lastYankSize + buflen - len;
                            truncated = true;
                        }
                        if (ucharCount > killRing.lastYankSize) {
                            memmove(buf32 + pos + ucharCount - killRing.lastYankSize,
                                    buf32 + pos,
                                    sizeof(UChar32) * (len - pos + 1));
                            memmove(buf32 + pos - killRing.lastYankSize,
                                    restoredText->get(),
                                    sizeof(UChar32) * ucharCount);
                        } else {
                            memmove(buf32 + pos - killRing.lastYankSize,
                                    restoredText->get(),
                                    sizeof(UChar32) * ucharCount);
                            memmove(buf32 + pos + ucharCount - killRing.lastYankSize,
                                    buf32 + pos,
                                    sizeof(UChar32) * (len - pos + 1));
                        }
                        pos += ucharCount - killRing.lastYankSize;
                        len += ucharCount - killRing.lastYankSize;
                        killRing.lastYankSize = ucharCount;
                        refreshLine(pi);
                        if (truncated) {
                            beep();
                        }
                        break;
                    }
                }
                beep();
                break;

#ifndef _WIN32
            case ctrlChar('Z'):
                disableRawMode();
                raise(SIGSTOP);
                enableRawMode();
                if (write32(1, pi.promptText.get(), pi.promptChars) == -1)
                    break;
                refreshLine(pi);
                break;
#endif


            case 127:
            case DELETE_KEY:
                killRing.lastAction = KillRing::actionOther;
                if (len > 0 && pos < len) {
                    historyRecallMostRecent = false;
                    memmove(buf32 + pos, buf32 + pos + 1, sizeof(UChar32) * (len - pos));
                    --len;
                    refreshLine(pi);
                }
                break;

            case META + '<':
            case PAGE_UP_KEY:
            case META + '>':
            case PAGE_DOWN_KEY:
                killRing.lastAction = KillRing::actionOther;


                if (historyIndex == historyLen - 1) {
                    free(history[historyLen - 1]);
                    size_t tempBufferSize = sizeof(UChar32) * len + 1;
                    unique_ptr<UChar8[]> tempBuffer(new UChar8[tempBufferSize]);
                    copyString32to8(tempBuffer.get(), buf32, tempBufferSize);
                    history[historyLen - 1] = reinterpret_cast<UChar8*>(
                        strdup(reinterpret_cast<const char*>(tempBuffer.get())));
                }
                if (historyLen > 1) {
                    historyIndex = (c == META + '<' || c == PAGE_UP_KEY) ? 0 : historyLen - 1;
                    historyPreviousIndex = -2;
                    historyRecallMostRecent = true;
                    size_t ucharCount;
                    int errorCode;
                    copyString8to32(buf32, history[historyIndex], buflen, ucharCount, errorCode);
                    len = pos = ucharCount;
                    refreshLine(pi);
                }
                break;


            default:
                killRing.lastAction = KillRing::actionOther;
                historyRecallMostRecent = false;
                if (c & (META | CTRL)) {
                    beep();
                    break;
                }
                if (len < buflen) {
                    if (isControlChar(c)) {
                        beep();
                        break;
                    }
                    if (len == pos) {
                        buf32[pos] = c;
                        ++pos;
                        ++len;
                        buf32[len] = '\0';
                        int inputLen = calculateColumnPosition(buf32, len);
                        if (pi.promptIndentation + inputLen < pi.promptScreenColumns) {
                            if (inputLen > pi.promptPreviousInputLen)
                                pi.promptPreviousInputLen = inputLen;


                            if (write32(1, reinterpret_cast<UChar32*>(&c), 1) == -1)
                                return -1;
                        } else {
                            refreshLine(pi);
                        }
                    } else {
                        memmove(buf32 + pos + 1, buf32 + pos, sizeof(UChar32) * (len - pos));
                        buf32[pos] = c;
                        ++len;
                        ++pos;
                        buf32[len] = '\0';
                        refreshLine(pi);
                    }
                } else {
                    beep();
                }
                break;
        }
    }
    return len;
}
