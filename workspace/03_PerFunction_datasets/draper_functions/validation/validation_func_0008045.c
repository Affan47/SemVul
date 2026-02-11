_PR_MakeNativeIPCName(
    const char *name,
    char *result,
    PRIntn size,
    _PRIPCType type)
{
    if (strlen(name) >= (PRSize)size) {
        PR_SetError(PR_BUFFER_OVERFLOW_ERROR, 0);
        return PR_FAILURE;
    }
    strcpy(result, name);
    switch (type) {
        case _PRIPCSem:
            _pr_ConvertSemName(result);
            break;
        case _PRIPCShm:
            _pr_ConvertShmName(result);
            break;
        default:
            PR_SetError(PR_INVALID_ARGUMENT_ERROR, 0);
            return PR_FAILURE;
    }
    return PR_SUCCESS;
}
