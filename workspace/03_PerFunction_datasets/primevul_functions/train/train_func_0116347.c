xz_error(xz_statep state, int err, const char *msg)
{

    if (state->msg != NULL) {
        if (state->err != LZMA_MEM_ERROR)
            xmlFree(state->msg);
        state->msg = NULL;
    }


    state->err = err;
    if (msg == NULL)
        return;


    if (err == LZMA_MEM_ERROR) {
        state->msg = (char *) msg;
        return;
    }


    if ((state->msg =
         xmlMalloc(strlen(state->path) + strlen(msg) + 3)) == NULL) {
        state->err = LZMA_MEM_ERROR;
        state->msg = (char *) "out of memory";
        return;
    }
    strcpy(state->msg, state->path);
    strcat(state->msg, ": ");
    strcat(state->msg, msg);
    return;
}
