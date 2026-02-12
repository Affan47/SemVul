int ExpressionRegex::execute(RegexExecutionState* regexState) const {
    invariant(regexState);
    invariant(!regexState->nullish());
    invariant(regexState->pcrePtr);

    int execResult = pcre_exec(regexState->pcrePtr.get(),
                               nullptr,
                               regexState->input->c_str(),
                               regexState->input->size(),
                               regexState->startBytePos,
                               0,
                               &(regexState->capturesBuffer.front()),
                               regexState->capturesBuffer.size());


    uassert(51156,
            str::stream() << "Error occurred while executing the regular expression in " << _opName
                          << ". Result code: " << execResult,
            execResult == -1 || (execResult > 0 && execResult <= (regexState->numCaptures + 1)));
    return execResult;
}
