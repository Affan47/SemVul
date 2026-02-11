read_commands(struct response_state *state,
              int sock)
{
        enum ntb_file_error file_error;
        ssize_t got;

        while (true) {
                ntb_buffer_ensure_size(&state->buf, state->buf.length + 512);

                got = read(sock,
                           state->buf.data + state->buf.length,
                           state->buf.size - state->buf.length);

                if (got == -1) {
                        set_response_error(state,
                                           &ntb_file_error,
                                           ntb_file_error_from_errno(errno),
                                           "Error reading from IPC socket: %s",
                                           strerror(errno));
                        break;
                } else if (got == 0) {
                        if (state->buf.length > 0) {
                                file_error = ntb_file_error_from_errno(errno);
                                set_response_error(state,
                                                   &ntb_file_error,
                                                   file_error,
                                                   "Invalid data received from "
                                                   "IPC socket: %s",
                                                   strerror(errno));
                        }
                        break;
                } else {
                        state->buf.length += got;
                        if (!process_commands(state, sock))
                                break;
                }
        }

        if (state->error == NULL && !state->had_response) {
                set_response_error(state,
                                   &ntb_ipc_client_error,
                                   NTB_IPC_CLIENT_ERROR_NO_RESPONSE,
                                   "No response received from IPC socket");
        }
}
