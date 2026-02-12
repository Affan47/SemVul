static int connection_read_cq_err(connection *con) {
    request_st * const r = &con->request;
  #if defined(__WIN32)
    int lastError = WSAGetLastError();
    switch (lastError) {
    case EAGAIN:
        return 0;
    case EINTR:

        con->is_readable = 1;
        return 0;
    case ECONNRESET:

        break;
    default:
        log_error(r->conf.errh, __FILE__, __LINE__,
          "connection closed - recv failed: %d", lastError);
        break;
    }
  #else
    switch (errno) {
    case EAGAIN:
        return 0;
    case EINTR:

        con->is_readable = 1;
        return 0;
    case ECONNRESET:

        break;
    default:
        log_perror(r->conf.errh, __FILE__, __LINE__,
          "connection closed - read failed");
        break;
    }
  #endif

    connection_set_state_error(r, CON_STATE_ERROR);
    return -1;
}
