sslerror(char *txt) {
    unsigned long err;
    char string[120];

    err=ERR_get_error();
    if(!err) {
        s_log(LOG_ERR, "%s: Peer suddenly disconnected", txt);
        return;
    }
    sslerror_queue();
    ERR_error_string(err, string);
    s_log(LOG_ERR, "%s: %lX: %s", txt, err, string);
}
