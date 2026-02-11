sortItems() {
    UErrorCode errorCode=U_ZERO_ERROR;
    uprv_sortArray(items, itemCount, (int32_t)sizeof(Item), compareItems, NULL, FALSE, &errorCode);
    if(U_FAILURE(errorCode)) {
        fprintf(stderr, "icupkg: sorting item names failed - %s\n", u_errorName(errorCode));
        exit(errorCode);
    }
}
