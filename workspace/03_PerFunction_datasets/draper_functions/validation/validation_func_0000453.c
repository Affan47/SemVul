add_zombie_request(LIBSSH2_SFTP *sftp, uint32_t request_id)
{
    LIBSSH2_SESSION *session = sftp->channel->session;

    struct sftp_zombie_requests *zombie;

    _libssh2_debug(session, LIBSSH2_TRACE_SFTP,
                   "Marking request ID %ld as a zombie request", request_id);

    zombie = LIBSSH2_ALLOC(sftp->channel->session,
                           sizeof(struct sftp_zombie_requests));
    if (!zombie)
        return _libssh2_error(session, LIBSSH2_ERROR_ALLOC,
                              "malloc fail for zombie request  ID");
    else {
        zombie->request_id = request_id;
        _libssh2_list_add(&sftp->zombie_requests, &zombie->node);
        return LIBSSH2_ERROR_NONE;
    }
}
