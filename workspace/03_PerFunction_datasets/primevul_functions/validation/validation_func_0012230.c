Value ExpressionRegex::nextMatch(RegexExecutionState* regexState) const {
    int execResult = execute(regexState);


    if (execResult < 0) {
        return Value(BSONNULL);
    }


    StringData input = *(regexState->input);

    auto verifyBounds = [&input, this](auto startPos, auto limitPos, auto isCapture) {


        if (startPos == -1 || limitPos == -1) {
            massert(31304,
                    str::stream() << "Unexpected error occurred while executing " << _opName
                                  << ". startPos: " << startPos << ", limitPos: " << limitPos,
                    isCapture && startPos == -1 && limitPos == -1);
            return;
        }

        massert(31305,
                str::stream() << "Unexpected error occurred while executing " << _opName
                              << ". startPos: " << startPos,
                (startPos >= 0 && static_cast<size_t>(startPos) <= input.size()));
        massert(31306,
                str::stream() << "Unexpected error occurred while executing " << _opName
                              << ". limitPos: " << limitPos,
                (limitPos >= 0 && static_cast<size_t>(limitPos) <= input.size()));
        massert(31307,
                str::stream() << "Unexpected error occurred while executing " << _opName
                              << ". startPos: " << startPos << ", limitPos: " << limitPos,
                startPos <= limitPos);
    };


    verifyBounds(regexState->capturesBuffer[0], regexState->capturesBuffer[1], false);
    const int matchStartByteIndex = regexState->capturesBuffer[0];
    StringData matchedStr =
        input.substr(matchStartByteIndex, regexState->capturesBuffer[1] - matchStartByteIndex);


    for (int byteIx = regexState->startBytePos; byteIx < matchStartByteIndex;
         ++(regexState->startCodePointPos)) {
        byteIx += getCodePointLength(input[byteIx]);
    }


    regexState->startBytePos = matchStartByteIndex;

    std::vector<Value> captures;
    captures.reserve(regexState->numCaptures);


    for (int i = 0; i < regexState->numCaptures; ++i) {
        const int start = regexState->capturesBuffer[2 * (i + 1)];
        const int limit = regexState->capturesBuffer[2 * (i + 1) + 1];
        verifyBounds(start, limit, true);


        captures.push_back(start == -1 && limit == -1 ? Value(BSONNULL)
                                                      : Value(input.substr(start, limit - start)));
    }

    MutableDocument match;
    match.addField("match", Value(matchedStr));
    match.addField("idx", Value(regexState->startCodePointPos));
    match.addField("captures", Value(captures));
    return match.freezeToValue();
}
