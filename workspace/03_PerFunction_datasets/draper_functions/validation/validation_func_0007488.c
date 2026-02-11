setStackLimit(int32_t limit, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return;
    }
    if (U_FAILURE(fDeferredStatus)) {
        status = fDeferredStatus;
        return;
    }
    if (limit < 0) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return;
    }


    reset();

    if (limit == 0) {

        fStack->setMaxCapacity(0);
    } else {


        int32_t adjustedLimit = limit / sizeof(int32_t);
        if (adjustedLimit < fPattern->fFrameSize) {
            adjustedLimit = fPattern->fFrameSize;
        }
        fStack->setMaxCapacity(adjustedLimit);
    }
    fStackLimit = limit;
}
