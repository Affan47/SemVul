static void handle_set_nonblocking(HANDLE fh)
{
    DWORD file_type, pipe_state;
    file_type = GetFileType(fh);
    if (file_type != FILE_TYPE_PIPE) {
        return;
    }


    if (!GetNamedPipeHandleState(fh, &pipe_state, NULL,
                                 NULL, NULL, NULL, 0)) {
        return;
    }

    if (pipe_state & PIPE_NOWAIT) {
        return;
    }

    pipe_state |= PIPE_NOWAIT;
    SetNamedPipeHandleState(fh, &pipe_state, NULL, NULL);
}
